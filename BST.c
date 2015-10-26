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

void BST_change_print_function( BST_t tree, printFunction func )
{
  tree->printFunc = func;
}

void BST_change_compare_function(BST_t tree, compareFunction func )
{
  tree->compFunc = func;
}

}
