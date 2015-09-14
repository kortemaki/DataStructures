#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#define STACK
#ifdef COUNTER
#undefine COUNTER
#endif

//Constant strings
const char* const VALID = "valid";
const char* const INVALID = "invalid";
const char* const UNCLOSED_PARENS_LENGTH = "Unclosed parentheses at end of string of length %d\n";
const char* const CANNOT_CLOSE_PAREN_AT_INDEX = "Cannot close the parentheses at index %d\n";
const char* const NONEMPTY_STACK_LENGTH = "Nonempty stack at end of string of length %d\n";
const char* const VALID_STRING_LENGTH = "Valid string of length %d\n";

//Character aliases
enum{ LEFT_PAREN = '(', RIGHT_PAREN = ')',
      LEFT_BRACE = '{', RIGHT_BRACE = '}',
      LEFT_BRACK = '[', RIGHT_BRACK = ']',
      STRING_END = '\0' };

//Character tokens
void* LEFT_PAREN_TOKEN = (void*) '(';
void* LEFT_BRACE_TOKEN = (void*) '{';
void* LEFT_BRACK_TOKEN = (void*) '[';

#ifdef COUNTER
int isValid(char* string)
{
    int leftNum = 0;
    int rightNum = 0;
    int seen = 0;
    char last;
    int i;
    int stringLength = strlen(string);
    for ( i = 0; i < stringLength; i++ )
    {
        if ( string[i] == '(' || string[i] == ')' )
	{
	    if( string[i] == '(' )
	    {
	        leftNum++;
	    }
	    else
	    {
		rightNum++;
	    }
	    last = string[i];
	    if ( leftNum < rightNum ) 
	    {
#ifdef DEBUG
                printf( CANNOT_CLOSE_PAREN_AT_INDEX, i );
#endif
  	        return 0;
	    }
	    seen == 1;
	}
    }
    if ( seen == 1 && last != ')' )
    {
#ifdef DEBUG
        printf( UNCLOSED_PARENS_LENGTH, stringLength );
#endif
        return 0;
    }
    if ( leftNum != rightNum )
    {
#ifdef DEBUG
        printf( VALID_STRING_LENGTH, stringLength );
#endif
        return 0;
    }
    return 1;
}
#endif
#ifdef STACK
int isValid(char* string)
{
    stack_t stack = stack_new();

    int i = -1;
    int stringLength = strlen(string);
    while(1)
    {
        i++;
        switch( string[i] )
	{
	    case LEFT_PAREN:	    
                stack_push(stack, LEFT_PAREN_TOKEN);
		      break;

	    case RIGHT_PAREN:
                if ( stack_is_empty(stack) || stack_pop(stack) != LEFT_PAREN_TOKEN )
		{
#ifdef DEBUG
		    printf( CANNOT_CLOSE_PAREN_AT_INDEX, i );
#endif
		    return 0;
 		}
		break;    

	    case LEFT_BRACE:
            stack_push(stack, LEFT_BRACE_TOKEN);
  	        break;

	    case RIGHT_BRACE:
            if ( stack_is_empty(stack) || stack_pop(stack) != LEFT_BRACE_TOKEN )
  	        break;

            case LEFT_BRACK:
            stack_push(stack, LEFT_BRACK_TOKEN);
  	        break;	

	    case RIGHT_BRACK:
            if ( stack_is_empty(stack) || stack_pop(stack) != LEFT_BRACK_TOKEN )
  	        break;

            case STRING_END:
	        if ( !stack_is_empty(stack) )
		{
#ifdef DEBUG
		    printf( NONEMPTY_STACK_LENGTH, stringLength);
#endif
		    return 0;
		}
#ifdef DEBUG
		printf( VALID_STRING_LENGTH, stringLength );
#endif
		return 1;

	    default:
	        continue;
	}
    }
}
#endif

int main( int argc, char **argv )
{
    if( argc < 2 )
    {
        printf( "Error: Must have at least one argument!" );
	exit(1);
    }

    int i;
    const char* qualifier;
    for( i = 1; i < argc; ++i )
    {
        qualifier = isValid( argv[i] ) ? VALID : INVALID;
        printf( "String %d: %s - %s\n", i, argv[i], qualifier );
    }

    return 0;
}
