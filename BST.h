#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#ifdef ENABLE_TYPECHECK
#undef ENABLE_TYPECHECK
#endif

void print_pointer( void* val, char* prefix );

int compare_pointer( void* p1, void* p2 );

typedef void (*printFunction)( void *, char* ); //print one element with a char* prefix

typedef int (*compareFunction)( void *, void * ); //compare two elements

////////////////////////////
// BST Node code

struct BinaryTreeNode
{
  void* data;                   //data for this node
  struct BinaryTreeNode* left;  //left subtree
  struct BinaryTreeNode* right; //right subtree
  compareFunction compFunc;     //function for comparing the data
  printFunction printFunc;      //function for printing the data
};
typedef struct BinaryTreeNode* BST_t;

/**
 * constructor for node
 * returns pointer to new node with NULL next
 * and uninitialized val field
 */
BST_t BST_new();

/**
 * constructor for node
 * returns pointer to new node with NULL next
 * and val field initialized to parameter x
 */
BST_t BST_new_val(void* x);

/**
 * Print the val in n
 * Then follow the chain of next pointers
 * and print any subsequent vals as well
 * until a NULL next pointer is reached
 * 
 * If n is NULL, do nothing
 */
void BST_print_in_order(BST_t n, char* prefix);

////////////////////////////
//  Binary search tree

#ifdef ENABLE_TYPECHECK
/**
 * Query method to check whether a list_t is a valid list
 * Returns 1 if tree is a BST
 * or 0 if it is not
 */
int BST_is_BST(BST_t tree);
#endif

/**
 * Method to query a tree for the length of its longest path from root to leaf
 */
int BST_height(BST_t tree);

/**
 * Add x as a leaf node in the tree
 */
void BST_insert(BST_t tree, void* x);

/**
 * Removes element x from the tree
 */
void BST_remove(BST_t tree, void* x);
 
/**
 * Method to return an element from the list (without removing it)
 * Returns the element which matches x under the tree's comparison function
*/
void* BST_find(BST_t tree, void* x);

void BST_change_print_function( BST_t list, printFunction func );

void BST_change_compare_function( BST_t tree, compareFunction func );

#endif
