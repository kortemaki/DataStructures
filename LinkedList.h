#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#ifdef ENABLE_TYPECHECK
#undef ENABLE_TYPECHECK
#endif

#define ENABLE_TYPECHECK

////////////////////////////
//  Node code

struct node
{
  void* val;
  struct node* next;
};
typedef struct node node;

/**
 * constructor for node
 * returns pointer to new node with NULL next
 * and uninitialized val field
 */
node* node_new();

/**
 * constructor for node
 * returns pointer to new node with NULL next
 * and val field initialized to parameter x
 */
node* node_new_val(void* x);

/**
 * Function to create a deep copy of a node chain
 * Returns a pointer to a new chain with the same values in the same order as the parameter n
 */
node* node_chain_clone( node* n );

/**
 * Print the val in n
 * Then follow the chain of next pointers
 * and print any subsequent vals as well
 * until a NULL next pointer is reached
 * 
 * If n is NULL, do nothing
 */
void node_print_chain(node* n);


////////////////////////////
//  List code

typedef void (*printFunction)( void *, char* );

/**
 * List header
 */
struct list_h
{
  int size; // How many elements are in the list
  int MAX_SIZE;
  node* start; // The first node in the list
  node* end; // The last node in the list
  printFunction printFunc;
};
typedef struct list_h* list_t;

/**
 * List constructor
 */
list_t list_new();

#ifdef ENABLE_TYPECHECK
/**
 * Query method to check whether a list_t is a valid list
 * Returns 1 if list is a list
 * or 0 if it is not
 */
int list_is_list(list_t list);
#endif

/**
 * Method to query a list for its size in number of elements
 */
int list_size(list_t list);

/**
 * Append x to the end of the list
 */
void list_append(list_t list, void* x);

/**
 * Prepend x to the beginning of the list
 */
void list_prepend(list_t list, void* x);

/**
 * Method to remove an element from the list
 * Returns the element which was previously at the index location in the list
 * and shifts all remaining elements appropriately
 */
void* list_remove(list_t list, int index);

/**
 * Method to return an element from the list (without removing it)
 * Returns the element which is located at the index location in the list
 */
void* list_get(list_t list, int index);

/**
 * Method to create a deep copy of a list
 * Returns a new list with the same values in the same order as the parameter list
 */
list_t list_clone(list_t list);

/**
 * Appends a list to the end of another list
 * The list returned is a copy of the elements in the two parameters
 *  and the ordered elements of list2 will be copied to the end of a copy list1
 */
list_t list_concatenate(list_t list1, list_t list2);

/**
 * Print the elements of a list in sequence
 * prefix will be prepended to each line printed
 */
void list_print_list(list_t list, char* prefix);

#endif
