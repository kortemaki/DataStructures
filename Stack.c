#include "Stack.h"

/**
 * Stack constructor
 */
stack_t stack_new()
{
  stack_t new = (stack_t) malloc(sizeof( struct stack_h ));
  new->elements = list_new(); //empty list to hold our elements
  list_change_print_function( new->elements, &print_pointer ); //default element printing function
  return new;
}

#ifdef ENABLE_TYPECHECK
/**
 * Query method to check whether a stack_t is a valid stack
 * Returns 1 if stack is a stack
 * or 0 if it is not
 */
int stack_is_stack( stack_t stack )
{
  if( stack == NULL )
    return 0;
  return list_is_list( stack->elements );
}
#endif


/**
 * Method to query a stack as to whether it has any elements
 */
int stack_is_empty( stack_t stack )
{
  return stack_size( stack ) == 0;
}

/**
 * Method to query a stack for its size in number of elements
 */
int stack_size( stack_t stack )
{
  list_size( stack->elements );
}

/**
 * Method to push a value onto the stack
 */
void stack_push( stack_t stack, void* val )
{
  list_prepend( stack->elements, val );
}

/**
 * Method to remove the top value from the stack and return it
 */
void* stack_pop( stack_t stack )
{
  return list_remove( stack->elements, 0 );
}

/**
 * Method to obtain the top value from the stack without removing it
 */
void* stack_peek( stack_t stack )
{
  return list_get( stack->elements, 0 );
}

/**
 * Method to reverse the order of the top two elements of stack
 */
void stack_swap( stack_t stack )
{
  void* val1 = stack_pop( stack );
  void* val2 = stack_pop( stack );
  stack_push( stack, val1 );
  stack_push( stack, val2 );
} 

void stack_change_print_function( stack_t stack, printFunction func )
{
  list_change_print_function( stack->elements, func );
}

/**
 * Method to print the elements of the stack in order from top to bottom
 */
void stack_print_stack( stack_t stack, char* prefix )
{
  printf( "%s=== Stack of size %d ===\n", prefix, stack_size(stack) );

  //set up prefix for element print function calls
  char innerPrefix[ strlen(prefix) + 3 ];
  strcpy( innerPrefix, prefix );
  strcpy( innerPrefix + strlen(prefix), "> " );

  printf( "%sList of Elements\n", innerPrefix );

  list_print_list( stack->elements, innerPrefix );

  printf( "%s=======================\n", prefix );
}
