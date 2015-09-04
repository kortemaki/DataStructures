#include "LinkedList.h"

////////////////////////////
//  Main
int main()
{
  int zero = 0;
  int one = 1;
  int two = 2;

  int i;
  
  node* n = node_new();
  n->val  = &one;
  n->next = NULL;
  node_print_chain( n );
  
  node m;
  m.val  = &two;
  m.next = n;
  node_print_chain( &m );

  n->next = &m;

  node* z = node_new();
  z->next = NULL;
  z->val = &zero;

  list_t list = list_new();
  list->start = n;
  list->size = 20;
  list->end = z;

  list_print_list(list, "");

  list_get(list, 0);


  /**
  node_print_chain( list->start );
  printf("Appending 321\n");
  for( i = 3; i > 0; i-- )
  {
    node_print_chain( list->start );
    list_append( list, i );
  }
  node_print_chain( list->start );

  printf("Removing the %dth element from the list gives %d\n", 1, list_remove( list, 1 ));
  node_print_chain( list->start );

  printf("Removing the %dth element from the list gives %d\n", 0, list_remove( list, 0 ));
  node_print_chain( list->start );

  //list_remove( list, 1 );
 

  list_t list1 = list_new();
  for( i = 3; i > 0; i-- )
  {
    list_append( list1, i );
  }
  list_t list2 = list_new();
  for( i = 6; i > 3; i-- )
  {
    list_append( list2, i );
  }

  printf("Printing list1\n");
  node_print_chain( list1->start );
  printf("Printing list2\n");
  node_print_chain( list2->start );

  list_t list3 = list_clone( list1 );
  printf("Printing list3 (copy of list1)\n");
  node_print_chain( list3->start );

  printf("Remove 2 from list1\n");
  list_remove( list1, 1 );
  printf("Append 0 to list1\n");
  list_append( list1, 0 );
  
  printf("Printing list1\n");
  node_print_chain( list1->start );
  if( !list_is_list( list1 ) )
    printf("LIST1 IS NOT A LIST!!!\n");

  printf("Printing list3\n");
  node_print_chain( list3->start );
  printf("List 3 has size: %d\n", list_size(list3));
  list_get(list3, 2);

  list_t list4 = list_concatenate(list1, list2); //310654

  list_t list5 = list_concatenate(list2, list1); //654310
  printf("Printing lists 1 thru 5 in order\n");
  node_print_chain( list1->start );
  node_print_chain( list2->start );
  node_print_chain( list3->start );
  node_print_chain( list4->start );
  node_print_chain( list5->start );
  */
}
