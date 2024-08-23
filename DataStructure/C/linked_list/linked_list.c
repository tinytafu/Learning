#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

void init_linked_list(node_t **pphead) {
  *pphead = NULL;
  return;
}
/*打印链表数据*/
void print_linked_list(node_t *phead) {
  if (phead == NULL)
    return;
  node_t *cur = phead;
  while (cur) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("\n");
}
/*头部插入数据元素*/
void insert_at_beginning(node_t **pphead, elem_t data) {
  if (pphead == NULL)
    return;
  // 申请新的结点
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  // 初始化新结点的数据
  new_node->next = NULL;
  new_node->data = data;
  // 若链表无数据元素
  if (NULL == *pphead) {
    *pphead = new_node;
    return;
  }
  // 若链表至少一个数据元素
  (new_node)->next = *pphead;
  *pphead = new_node;
  return;
}
/*尾部插入数据元素*/
void insert_at_end(node_t **pphead, elem_t data) {
  if (pphead == NULL)
    return;
  // 申请新的结点
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  // 初始化新结点的数据
  new_node->next = NULL;
  new_node->data = data;
  // 若链表无数据元素
  if (*pphead == NULL) {
    *pphead = new_node;
    return;
  }
  // 若链表至少一个数据元素
  // 申请一个cur指针指向当前头结点
  node_t *cur = *pphead;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  // 当前cur指向尾部结点,插入数据元素
  cur->next = new_node;
  return;
}
/*头部删除数据元素*/
void delete_from_beginning(node_t **pphead) {
  // 若pphead为空或者链表为空
  if (pphead == NULL || *pphead == NULL)
    return;
  // 保存需要删除的头结点的地址
  node_t *cur = *pphead;
  *pphead = (*pphead)->next;
  // 释放原头结点的所在的内存空间
  free(cur);
  return;
}
/*尾部删除数据元素*/
void delete_from_end(node_t **pphead) {
  if (pphead == NULL || *pphead == NULL)
    return;
  // 申请一个cur,pre指针分别指向头结点
  node_t *cur = *pphead;
  node_t *pre = *pphead;
  while (cur->next) {
    // pre指向cur当前指向的结点
    pre = cur;
    // cur指向下一个结点
    cur = cur->next;
  }
  // 此时cur指向当前尾部结点,pre指向尾部结点的上一个结点
  free(cur);
  pre->next = NULL;
  return;
}
/*删除特定位置上的数据元素*/
void delete_at_pos(node_t **pphead, int pos) {
  if (pphead == NULL || *pphead == NULL)
    return;
  // 若pos == 1,则是头部删除
  if (pos == 1) {
    delete_from_beginning(pphead);
    return;
  }
  // 从头结点顺序遍历链表的个数
  int count = 1;
  // pre指针指向当前头结点
  node_t *pre = *pphead;
  while ((count + 1) != pos && pre->next != NULL) {
    pre = pre->next;
    count++;
  }
  // 此时pre指向需要删除结点的前一个结点
  // del指针指向需要删除的结点
  node_t *cur = pre->next;
  pre->next = cur->next;
  free(cur);
  return;
}

/*--------------题目实现----------------*/
node_t *reversal(node_t *phead) {
  // 若phead为NULL返回phead,若链表只有一个数据元素也返回phead
  if (phead == NULL || phead->next == NULL)
    return phead;
  // 定义三个指针变量分别指向NULL,链表的头结点,头结点的后一个结点
  node_t *n1 = NULL;
  node_t *n2 = phead;
  node_t *n3 = phead->next;
  // 若n2不为NULL
  while (n2) {
    // 当前结点的指向,指向前一个结点
    n2->next = n1;
    // 三个指针分别后移一个结点位置
    n1 = n2;
    n2 = n3;
    // 若n3为NULL,则n3不再后移动,否则发生空指针的解引用
    if (n3 != NULL)
      n3 = n3->next;
  }
  // 此时n3 == NULL,n2 == NULL,n1指向翻转后的头结点
  return n1;
}
node_t *reversal_two(node_t *phead) {
  if (phead == NULL || phead->next == NULL)
    return phead;
  // cur指向要插入新链表的结点 -- 从头结点开始
  node_t *cur = phead;
  // next保存要插入新链表结点的后一个结点 --
  // 防止cur插入新链表之后,后结点找不到了
  node_t *next = phead->next;
  // 新链表的头指针
  node_t *new_head = NULL;
  while (cur) { // cur指向NULL代表旧链表无结点插入
    // 头插法将结点插入新链表
    cur->next = new_head;
    new_head = cur;
    // cur指向要插入的新的结点
    cur = next;
    // next指向要插入新的结点的下一个结点
    if (next)
      next = next->next;
  }
  return new_head;
}
