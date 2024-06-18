#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
/*0.遍历链表*/
void traversal_linked_list(node_t *head) {
  if (NULL == head)
    return;
  while (NULL != head) {
    printf("%d->", head->data);
    head = head->next;
  }
  printf("NULL\n");
  return;
}
/*0.链表长度*/
void length_linked_list(node_t *head, unsigned short *length) {
  // 先将length指向的对象初始化为0
  *length = 0;
  // 若head为NULL,*length = 0
  if (NULL == head)
    return;
  while (NULL != head) {
    (*length)++;
    head = head->next;
  }
  return;
}
/*1.尾部插入结点*/
void push_back_linked_list(node_t **head, elem_t data) {
  // 分配一个结点
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (NULL == new_node) {
    printf("allocate failed!\n");
    return;
  }
  // 初始化结点数据
  new_node->data = data;
  new_node->next = NULL;
  // 若链表无结点,则new_node作为链表的第一个结点
  if (NULL == *head) {
    *head = new_node;
    return;
  }
  /*
   * 若链表至少一个结点,则将new_node作为插入到链表尾部为最后一个结点
   * 1.创建一个node_t*类型的tail指针用于找到链表中的尾部结点
   * 2.将tail->next指向new_node即可.
   */
  // tail指向链表中第一个结点
  node_t *tail = *head;
  // 若tail->next当前指向不为NULL
  while (NULL != tail->next)
    // 则移动tail指向下一个结点
    tail = tail->next;
  // tail目前指向链表尾部结点,将tail->next指向new_node
  tail->next = new_node;
  return;
}
