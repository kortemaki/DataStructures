#include "LinkedList.h"

////////////////////////////
// Message strings

const char* IndexOutOfBoundsError = "Illegal argument: Index out of bounds\n";
const char* IllegalListArgumentError = "Illegal argument: Invalid list\n";
const char* ImproperListBehaviorError = "Error: improper behavior: List no longer valid!\n";

////////////////////////////
//  Node code

/**
 * constructor for node
 * returns pointer to new node with NULL next
 * and uninitialized val field
 */
node* node_new()
{
  node* n = (node*) malloc(sizeof( node ));
  n->next = NULL;
  return n;
}

/**
 * constructor for node
 * returns pointer to new node with NULL next
 * and val field initialized to parameter x
 */
node* node_new_val(void* x)
{
  node* n = (node*) malloc(sizeof( node ));
  n->val = x;
  n->next = NULL;
  return n;
}

/**
 * Function to create a deep copy of a node chain
 * Returns a pointer to a new chain with the same values in the same order as the parameter n
 */
node* node_chain_clone( node* n )
{
  if( n == NULL )
    return NULL;
  node* new = node_new_val( n->val );
  new->next = node_chain_clone( n->next );
  return new;
}

/**
 * Print the val in n
 * Then follow the chain of next pointers
 * and print any subsequent vals as well
 * until a NULL next pointer is reached
 * 
 * If n is NULL, do nothing
 */
void node_print_chain(node* n)
{
  if(n != NULL)
  {
    printf("------------------");
    while(n != NULL)
    {
      printf("\n\tAddress: %p\n", n->val);
      n = n->next;
    }
    printf("------------------\n");
  }
}

void print_pointer( void* el, char* prefix )
{
  printf("\n%sAddress: %p\n", prefix,el);
}

////////////////////////////
//  List code

/**
 * List constructor
 */
list_t list_new()
{
  list_t new = (list_t) malloc(sizeof( struct list_h ));
  new->size = 0;
  new->start = NULL;
  new->end = NULL;
  new->printFunc = &print_pointer; //by default, print the addresses of each element
  return new;
}

#ifdef ENABLE_TYPECHECK
/**
 * Query method to check whether a list_t is a valid list
 * Returns 1 if list is a list
 * or 0 if it is not
 */
int list_is_list(list_t list)
{
  // Ensuring list is not NULL
  if( list == NULL )
  {
    printf("        Null list invalid\n");
    return 0;
  }

  // Check start and end are appropriate given size
  if( list->size == 0 )
  {
    // We should have NULL start and end
    if(list->start==NULL && list->end==NULL)
      return 1;
    else
    {
      printf("        List of size 0 invalid\n");
      return 0;
    }
  } 
  else if( list->size == 1 )
  {
    // We should have only one non-NULL node with a NULL next pointer
    if( !( list->start != NULL 
        && list->start == list->end 
        && list->end->next == NULL ) )
    {
      printf("        List of size 1 invalid\n");
      return 0;
    }
  }   
  else
  {
    // We should have more than one non-NULL node and end should have a NULL next
    if( !( list->start != NULL && list->end != NULL
        && list->start != list->end 
        && list->end->next == NULL ) )
    {
      printf("        List of size 2+ invalid\n");
      return 0;
    }
  }

  // Check if list->start is circular
  node* singles = list->start; // Walk down the list one node at a time
  node* doubles = list->start; // Walk down the list two nodes at a time
  while( doubles != NULL && singles != doubles )
  {
    singles = singles->next;
    doubles = doubles->next;
    if(doubles != NULL)
      doubles = doubles->next;
  }
  if( singles == doubles )
  {
    // Detected circular condition
    printf("        Circular linked list invalid\n");
    return 0;
  }

  // Check that the list terminates appropriately
  node* n = list->start;
  int count = 0;
  while( n != NULL && n != list->end && count < list->size )
  {
    count++;
    n = n->next;
  }
  // Ensure the last node in list is list->end
  if( n != list->end )
  {
    printf("        Final node of list invalid\n");
    return 0;
  }
  count++;
  // Ensure the length of list is equal to its size
  if( count != list->size )
  {
    printf("        List length invalid\n");
    return 0;
  }

  // Conclude: list is a list
  return 1;
} 
#endif

/**
 * Method to query a list for its size in number of elements
 */
int list_size(list_t list)
{

#ifdef ENABLE_TYPECHECK
  if( !list_is_list( list ) )
  {
    printf("%s",IllegalListArgumentError);
    exit(-1);
  }
#endif

  return list->size;
} 

/**
 * Append x to the end of the list
 */
void list_append(list_t list, void* x)
{

#ifdef ENABLE_TYPECHECK
  if( !list_is_list( list ) )
  {
    printf("%s", IllegalListArgumentError);
    exit(-1);
  }
#endif

  // Create new node with proper val
  node* new = node_new_val(x);

  // Add new node to list
  if( list_size(list)==0 )
  {
    // We are adding the first node in list
    list->start = new;
    list->end   = new;
  }
  else
  {
    // List has existing nodes
    node* prev = list->end;
    list->end  = new;
    prev->next = list->end;
  }

  // Update size of list
  list->size++;

#ifdef ENABLE_TYPECHECK
  // Debug statement
  if( !list_is_list( list ) )
  {
    printf("%s", ImproperListBehaviorError);
    exit(-1);
  }
#endif
}

/**
 * Prepend x to the beginning of the list
 */
void list_prepend(list_t list, void* x)
{
#ifdef ENABLE_TYPECHECK
  if( !list_is_list( list ) )
  {
    printf("%s", IllegalListArgumentError);
    exit(-1);
  }
#endif

  // Create new node with proper val
  node* new = node_new_val(x);

  // Add new node to list
  if( list_size(list)==0 )
  {
    // We are adding the first node in list
    list->start = new;
    list->end   = new;
  }
  else
  {
    // List has existing nodes
    new->next = list->start;
    list->start = new;
  }

  // Update size of list
  list->size++;

#ifdef ENABLE_TYPECHECK
  // Debug statement
  if( !list_is_list( list ) )
  {
    printf("%s", ImproperListBehaviorError);
    exit(-1);
  }
#endif
}

/**
 * Method to remove an element from the list
 * Returns the element which was previously at the index location in the list
 * and shifts all remaining elements appropriately
 */
void* list_remove(list_t list, int index)
{
#ifdef ENABLE_TYPECHECK
  if( !list_is_list( list ) )
  {
    printf("%s", IllegalListArgumentError);
    exit(-1);
  }
#endif
  if( index < 0 || index >= list_size(list) )
  {
    printf("%s", IndexOutOfBoundsError);
    exit(-1);
  }

  // Find the index'th node and its predecessor
  node* prev;
  node* n = list->start;
  int i;
  for( i = 0; i < index; i++ )
  {
    prev = n; 
    n = prev->next;
  } 

  // Update the pointers to remove n from the list
  if( index == 0 )
  {
    // There are no nodes before n
    list->start = n->next; //remove n
    
    // See if we removed the last node from the list
    if( list->start == NULL )
    {
      list->end = NULL;
    }
  }
  else
  {
    prev->next = n->next; //remove n
    if( index == list->size - 1 )
    {
      // We just removed the last node from list
      list->end = prev;
    }
  }  
  list->size--; // list has one fewer node

#ifdef ENABLE_TYPECHECK
  // Debug statement
  if( !list_is_list( list ) )
  {
    printf("%s", ImproperListBehaviorError);
    exit(-1);
  }
#endif

  // Get the value to return
  void* value = n->val;

  // Free n
  free(n);

  return value;
}

/**
 * Method to return an element from the list (without removing it)
 * Returns the element which is located at the index location in the list
 */
void* list_get(list_t list, int index)
{
#ifdef ENABLE_TYPECHECK
  // Typecheck list argument
  if( !list_is_list( list ) )
  {
    printf("%s", IllegalListArgumentError);
    exit(-1);
  }
#endif
  // Make sure index argument is valid
  if( index < 0 || index >= list_size(list) )
  {
    printf("%s", IndexOutOfBoundsError);
    exit(-1);
  }

  // Find the index'th node
  node* n = list->start;
  int i;
  for( i = 0; i < index; i++ )
  {
    n = n->next;
  }

  // Return its value
  return n->val;
}

/**
 * Appends a list to the end of another list
 * The list returned is a copy of the elements in the two parameters
 *  and the ordered elements of list2 will be copied to the end of a copy list1
 */
list_t list_concatenate(list_t list1, list_t list2)
{
#ifdef ENABLE_TYPECHECK
  // Typecheck list1 argument
  if( !list_is_list( list1 ) )
  {
    printf("%s", IllegalListArgumentError);
    exit(-1);
  }
  // Typecheck list2 argument
  if( !list_is_list( list2 ) )
  {
    printf("%s", IllegalListArgumentError);
    exit(-1);
  }
#endif

  // Detatches the pointers list1 and list2 from the actual lists
  // By creating a deep copy of each list before concatenating
  list1 = list_clone(list1);
  list2 = list_clone(list2);

  // See if list1 has any elements
  if( list1->size == 0 )
  {
    // Our final list looks just like list2
    list1->start = list2->start;
    list1->end = list2->end;
  }
  else
  {
    // Add list2 to the end of list1
    list1->end->next = list2->start;
    list1->end = list2->end;
  }
  // Update size of final list
  list1->size += list2->size;

  // Free list2's header (its nodes are part of list1)
  free(list2);

#ifdef ENABLE_TYPECHECK
  // Debug statement
  if( !list_is_list( list1 ) )
  {
    printf("%s", ImproperListBehaviorError);
    exit(-1);
  }
#endif

  // Return the concatenated list
  return list1;
}

/**
 * Method to create a deep copy of a list
 * Returns a new list with the same values in the same order as the parameter list
 */
list_t list_clone(list_t list)
{
#ifdef ENABLE_TYPECHECK
  // Typecheck list argument
  if( !list_is_list( list ) )
  {
    printf("%s", IllegalListArgumentError);
    exit(-1);
  }
#endif

  list_t new = list_new();
  if( list->size != 0 ) 
  { 
    // We need to copy the nodes in list before we are finished cloning
    // call recursive function get new node chain
    new->start = node_chain_clone( list->start );
    // walk down new chain to find end
    node* last = new->start;
    int i;
    for( i = list->size - 1; i > 0; i-- )
    {
      last = last->next;
    }
    new->end = last;
    new->size = list->size;
  }    

#ifdef ENABLE_TYPECHECK
  // Debug statement
  if( !list_is_list( new ) )
  {
    printf("%s", ImproperListBehaviorError);
    exit(-1);
  }
#endif

  // Return the cloned list
  return new;
}

void list_change_print_function( list_t list, printFunction func )
{
  list->printFunc = func;
}

void list_print_list( list_t list, char* prefix )
{
#ifdef ENABLE_TYPECHECK
  // Typecheck list argument
  if( !list_is_list( list ) )
  {
    printf( "%s", IllegalListArgumentError );
    exit(-1);
  }
#endif
  
  //create prefix for element print functions
  char innerPrefix[ strlen(prefix) + 3 ];
  strcpy( innerPrefix, "  " );
  strcpy( innerPrefix + 2, prefix );

  node* n = list->start;
  int count = list->size;
  printf( "%s--- List of size %d ---", prefix, count );
  while( n != NULL && count > 0 )
  {
    list->printFunc( n->val, innerPrefix );
    n = n->next;
    count--;
  }
  printf( "%s------------------------\n", prefix );
}
