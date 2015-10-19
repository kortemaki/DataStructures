#include "BST.h"

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
BST_t BST_new()
{
  BST_t t = (BST_t) malloc(sizeof( struct BinaryTreeNode ));
  t->left = NULL;
  t->right = NULL;
  t->data = NULL;
  t->printFunction = &print_pointer;
  t->compareFunction = &compare_pointer;
  return t;
}

/**
 * constructor for node
 * returns pointer to new node with NULL next
 * and val field initialized to parameter x
 */
BST_t BST_new_val(void* x)
{
  BST_t t = BST_new();
  t->data = x;
  return t;
}

/**
 * constructor for node
 * returns pointer to new node with NULL next
 * and uninitialized val field
 * Copies the compare and print functions of tree
 */
BST_t BST_new_like(BST_t tree)
{
  BST_t t = BST_new();
  t->printFunction = tree->printFunction;
  t->compareFunction = tree->compareFunction;
  return t;
}


/**
 * In order traversal print function
 * 
 * If n is NULL, do nothing
 */
void BST_print_in_order(BST_t t, char* prefix)
{
  char innerPrefix[ strlen(prefix) + 3 ];
  strcpy( innerPrefix, prefix );
  strcat( innerPrefix, "  " );

  if(t != NULL)
  {
    //print left subtree
    BST_print_in_order(t->left, innerPrefix);
    
    //print root data
    t->printFunction(t->data,prefix);

    //print right subtree
    BST_print_in_order(t->right, innerPrefix);
  }
}

void print_pointer( void* el, char* prefix )
{
  printf("\n%sAddress: %p\n%s", prefix, el, prefix);
}

/**
 * Compares two pointer valuesj
 * Returns zero if p1==p2
 *  and a positive value if p1 > p2
 *  else a negative value
 */
int compare_pointer( void* p1, void* p2 )
{
  return (int) (p1 - p2);
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
    return 1;
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
  if( singles == doubles && singles != NULL )
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
 * Method to query a tree for the length of its longest path from root to leaf
 */
int BST_height(BST_t tree)
{

#ifdef ENABLE_TYPECHECK
#endif

  if(tree==NULL)
  {
    return 0;
  }

  int heightLeft = BST_height(tree->left);
  int heightRight = BST_height(tree->right);

  int max = heightRight;
  if (heightLeft > heightRight)
  {
    max = heightLeft;
  }
  return 1 + max;
} 

/**
 * Add x into the BST as a leaf node according to the sorted order
 */
void BST_insert(BST_t tree, void* x)
{

#ifdef ENABLE_TYPECHECK
  
#endif

  if(tree != NULL)
  {

    //look up x in the tree
    // compare x with tree->data
    if(tree->compareFunction(tree->data, x)==0)
    {
      //if x is already in the tree
      //  replace the data with x
      tree->data = x;
      return;
    }
    else if(tree->compareFunction(tree->data,x) > 0)
    {
      //x in left subtree
      
      if(tree->left == NULL)
      {
	//we don't have a left subtree-- need to make one!
	tree->left = BST_new_like(tree);
	tree->left->data = x;
	return;
      }
    
      // recursively insert into left subtree
      BST_insert(tree->left, x);
      return;
    }
    else
    {
      //x in right subtree
      
      if(tree->right == NULL)
      {
	//we don't have a right subtree-- need to make one!
	tree->right = BST_new_like(tree);
	tree->right->data = x;
	return;
      }
    
      // recursively insert into right subtree
      BST_insert(tree->rightt, x);
      return;
    }
  }

#ifdef ENABLE_TYPECHECK
  
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
 * Returns the element which matches x under the tree's comparison function
 */
void* BST_find(BST_t tree, void* x)
{
#ifdef ENABLE_TYPECHECK
#endif

  if(tree != NULL)
  {

    //look up x in the tree
    // compare x with tree->data
    if(tree->compareFunction(tree->data, x)==0)
    {
      //We found a match!
      return tree->data;
    }
    else if(tree->compareFunction(tree->data,x) > 0)
    {
      //x in left subtree      
      return BST_find(tree->left, x);
    }
    else
    {
      //x in right subtree
      return BST_find(tree->right, x);
    }
  }
  else
    return NULL;
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
  strcpy( innerPrefix, prefix );
  strcpy( innerPrefix + strlen(prefix), "  " );

  node* n = list->start;
  int count = list->size;
  printf( "%s---- List of size %d ----\n%s", prefix, count, prefix );
  while( n != NULL && count > 0 )
  {
    list->printFunc( n->val, innerPrefix );
    n = n->next;
    count--;
  }
  printf( "\n%s------------------------\n", prefix );
}
