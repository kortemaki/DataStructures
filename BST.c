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
  t->printFunc = &print_pointer;
  t->compFunc = &compare_pointer;
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
  t->printFunc = tree->printFunc;
  t->compFunc = tree->compFunc;
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
    t->printFunc(t->data,prefix);

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
 *   implied by the BST's compare function.
 */
void BST_insert(BST_t tree, void* x)
{

#ifdef ENABLE_TYPECHECK
  
#endif

  if(tree != NULL)
  {

    //look up x in the tree
    // compare x with tree->data
    if(tree->compFunc(tree->data, x)==0)
    {
      //if x is already in the tree
      //  replace the data with x
      tree->data = x;
      return;
    }
    else if(tree->compFunc(tree->data,x) > 0)
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
      BST_insert(tree->right, x);
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
    if(tree->compFunc(tree->data, x)==0)
    {
      //We found a match!
      return tree->data;
    }
    else if(tree->compFunc(tree->data,x) > 0)
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

void BST_change_compare_function( BST_t tree, compareFunction func )
{
  tree->compFunc = func;
}

void print_int( void* el, char* prefix )
{
  printf("\n%sValue: %d\n%s", prefix, (int) el, prefix);
}

/**
 * convert int to binary
 */
char *int_to_binary(int x)
{
  char* b = malloc(sizeof(int)*8+1);
  b[0] = '\0';

  int i;
  for (i = sizeof(int)*8 - 1; i >= 0; i--)
  {
    size_t z = 1 << i;
    strcat(b, ((x & z) == z) ? "1" : "0");
  }

  return b;
}

void print_binary( void* el, char* prefix )
{
  char* val = int_to_binary((int) el);
  printf("\n%sValue: %d_10 = %s_2 (%d 1s)\n%s", prefix, (int) el, val, count_ones(val), prefix);
}

/**
 * Compares two int values
 * Returns zero if p1==p2
 *  and a positive value if p1 > p2
 *  else a negative value
 */
int compare_int( void* p1, void* p2 )
{
  return (int) (p1 - p2);
}

int count_ones(char* x)
{
  int count;
  for(count = 0; *x != '\0'; x++)
  {
    if(*x == '1')
      count++;
  }
  return count;
}

int compare_ones( void* p1, void* p2 )
{
  int onesComp = compare_int((void*) count_ones(int_to_binary((int) p1)), 
			     (void*) count_ones(int_to_binary((int) p2)));
  if(onesComp == 0)
    return -compare_int(p1,p2);
  else
    return onesComp;
}

///////////////////////////////////////////////////

/**
 * Basic script to demonstrate functionality of binary search tree
 * Adds the values 1 through 10 to a BST and print the tree at each step
 */
int main()
{

  BST_t tree = BST_new_val((void*) rand());
  BST_change_compare_function(tree, &compare_ones);
  BST_change_print_function(tree, &print_binary);

  int i;
  for( i = 9; i >= 1; i-- )
  {
    printf("\n----------------------------\n");
    
    BST_insert( tree, (void*) rand() );
    BST_print_in_order( tree, "" );
  }

  return 0;
}


