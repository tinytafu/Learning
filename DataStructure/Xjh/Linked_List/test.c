#include "linked_list.h"
#include <stdio.h>

int main() {
  // 创建一个指向链表头结点的指针
  node_t *head = NULL;
  // 尾部插入三个结点
  for (int i = 0; i < 5; i++) {
    push_back_linked_list(&head, i);
  }
  traversal_linked_list(head);
  for (int i = 0; i < 4; i++)
    pop_back_linked_list(&head);
  traversal_linked_list(head);
  pop_back_linked_list(&head);
  traversal_linked_list(head);
}
