#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct node node_t;
typedef int elem_t;

typedef enum {
  FALSE,
  TRUE,
} bool_t;

// 定义一个结构体类型表示链表中的结点类型
struct node {
  // 结点中的数据
  elem_t data;
  // 下一个结点的地址
  node_t *next;
};

#endif

/*遍历链表中结点的数据*/
void traversal_linked_list(node_t *head);

/*将新结点插入到链表的尾部*/
bool_t push_back_linked_list(node_t **head, elem_t data);

/*删除链表中的尾部元素*/
bool_t pop_back_linked_list(node_t **head);
