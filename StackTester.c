#include "Stack.h"

int main()
{

  int zero = 0;
  int one = 1;
  int two = 2;

  stack_t stack = stack_new();

  stack_print_stack(stack, "");

  stack_push( stack, &zero );
  stack_push( stack, &one );
  stack_push( stack, &two );
 
  stack_print_stack(stack, "");

  stack_pop( stack );

  stack_print_stack(stack, "");

  return 0;
}
