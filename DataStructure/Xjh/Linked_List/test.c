#include "linked_list.h"
#include <stdio.h>

int main() {
  // 创建一个无结点的链表
  node_t *head = NULL;
  // 插入三个数据:1,2,3
  push_back_linked_list(&head, 1);
  push_back_linked_list(&head, 2);
  push_back_linked_list(&head, 3);

  // 获取链表长度
  unsigned short length = 0;
  length_linked_list(head, &length);
  printf("length is %hd\n", length);

  // 打印链表中每个结点的数据
  traversal_linked_list(head);
}
