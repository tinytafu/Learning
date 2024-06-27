// 一个线程用于创建一个链表,另外一个线程用于打印
#include <tytofu.h>
typedef int elem_t;
typedef struct node {
  elem_t data;
  struct node *next;
} node_t;

// 描述链表
struct describe_list {
  node_t *head;
};
// 头插入法
void head_insert(node_t **pphead, elem_t data) {
  // 生成一个新的结点
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (new_node == NULL) {
    printf("malloc failed!\n");
    return;
  }
  new_node->next = NULL;
  new_node->data = data;
  if (NULL == *pphead) {
    *pphead = new_node;
    return;
  }
  new_node->next = *pphead;
  *pphead = new_node;
  return;
}
void tail_insert(node_t **pphead, elem_t data) {
  // 生成一个新的结点
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (NULL == new_node) {
    printf("malloc failed!\n");
    return;
  }
  new_node->next = NULL;
  new_node->data = data;
  if (*pphead == NULL) {
    *pphead = new_node;
    return;
  }
  if ((*pphead)->next == NULL) {
    (*pphead)->next = new_node;
    return;
  }
  node_t *tail = *pphead;
  while (tail->next != NULL) {
    tail = tail->next;
  }
  tail->next = new_node;
  return;
}
void print_list(node_t *head) {
  if (NULL == head) {
    printf("NULL\n");
    return;
  } else {
    node_t *cur = head;
    while (cur) {
      printf("%d ", cur->data);
      cur = cur->next;
    }
    printf("\n");
  }
}
void *threadA(void *arg) {
  struct describe_list *list = (struct describe_list *)arg;
  print_list(list->head);
  return NULL;
}

int main(int argc, char *argv[]) {
  // 创建一个描述链表的对象
  struct describe_list list;
  // 忘记初始化是个致命的问题
  list.head = NULL;
  for (int i = 0; i < 10; i++)
    head_insert(&list.head, i);
  // 创建1个线程,主线程用于插入,一个线程用于打印链表数据
  pthread_t tid;
  if (pthread_create(&tid, NULL, threadA, (void *)&list) != 0) {
    return 1;
  }
  pthread_join(tid, NULL);
  return EXIT_SUCCESS;
}
