#ifndef STACK_H
#define STACK_H

#include "LinkedList.h" //include 3

typedef void (*printFunction)( void *, char * );

struct stack_h
{
  list_t elements; //Element 0 in elements is the top of the stack
  printFunction printFunc;
};
typedef struct stack_h* stack_t;

/**
 * Stack constructor
 */
stack_t stack_new();

#ifdef ENABLE_TYPECHECK
/**
 * Query method to check whether a stack_t is a valid stack
 * Returns 1 if stack is a stack
 * or 0 if it is not
 */
int stack_is_stack( stack_t stack );
#endif

/**
 * Method to query a stack for its size in number of elements
 */
int stack_size( stack_t stack );

/**
 * Method to query a stack as to whether it has any elements
 */
int stack_is_empty( stack_t stack );

/**
 * Method to push a value onto the stack
 */
void stack_push( stack_t stack, void* val );

/**
 * Method to remove the top value from the stack and return it
 */
void* stack_pop( stack_t stack );

/**
 * Method to obtain the top value from the stack without removing it
 */
void* stack_peek( stack_t stack );

/**
 * Method to reverse the order of the top two elements of stack
 */
void stack_swap( stack_t stack );

void stack_print_stack( stack_t stack, char* prefix );

#endif
