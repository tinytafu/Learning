#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 生成链表结点
node_t *create_node(elem_t data) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (NULL == new_node) {
    printf("malloc filed!\n");
    return NULL;
  }
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}
// 尾部插入
bool_t push_back_linked_list(node_t **head, elem_t data) {

  // 判断head是否为NULL,当前链表无结点
  if (NULL == *head) {
    node_t *tmp = create_node(data);
    if (NULL == tmp) {
      printf("call create_node function failed!\n");
      return FALSE;
    }
    *head = tmp;
    return TRUE;
  } else {
    // 定义一个node_t*的tail指针,利用tail找到链表的尾部结点
    node_t *tail = *head;
    // 遍历链表结点,当tail->next为NULL遍历结束
    while (tail->next)
      tail = tail->next;
    node_t *tmp = create_node(data);
    if (NULL == tmp) {
      printf("call create_node function failed!\n");
      return FALSE;
    }
    tail->next = tmp;
    return TRUE;
  }
}
// 尾部删除
bool_t pop_back_linked_list(node_t **head) {
  // 若链表为空
  if (NULL == *head)
    return TRUE;
  else if (NULL == (*head)->next) {
    *head = NULL;
    return TRUE;
  } else {
    // 创建一个node_t*类型的prev指针
    node_t *prev = NULL;
    node_t *tail = *head;
    while (tail->next != NULL) {
      prev = tail;
      tail = tail->next;
    }
    // 此时tail指向尾部最后一个结点
    free(tail);
    tail = NULL;
    prev->next = NULL;
    return TRUE;
    // node_t *cur = *head;
    // while (NULL != cur->next->next) {
    //   cur = cur->next;
    // }
    // // 此时cur指向倒数第二个结点
    // free(cur->next);
    // cur->next = NULL;
    // cur->next = NULL;
    // return TRUE;
  }
}
// 遍历链表
void traversal_linked_list(node_t *head) {
  if (NULL == head) {
    printf("linked_list is empty!\n");
    exit(1);
  }
  // 定义一个node_t*的cur指针,cur指向head当前指向的对象
  node_t *cur = head;
  // 利用cur遍历链表,当其不为NULL继续
  while (cur) {
    printf("%d->", cur->data);
    // 指向下一个结点
    cur = cur->next;
  }
  printf("NULL\n");
}
