#include "linked_list.h"
#include <stdio.h>
int main() {
  node_t *head;
  init_linked_list(&head);
  for (int i = 0; i < 1; i++) {
    insert_at_beginning(&head, i);
    print_linked_list(head);
  }
  head = reversal_two(head);
  print_linked_list(head);
}
