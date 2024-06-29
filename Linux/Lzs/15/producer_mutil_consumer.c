// 生产者与消费者
// 消费者一次性消费5个
#include <tytofu.h>

typedef int elem_t;
// 定义一个结点的类型
typedef struct link_list {
  elem_t data;
  struct link_list *next;
} link_list_t;
// 定义一个共享数据的类型用于保存共享数据
typedef struct share {
  // 指向链表头结点的头指针
  link_list_t *phead;
  // 链表结点的数量
  int count;
  // 互斥锁
  pthread_mutex_t mutex;
  // 条件变量
  pthread_cond_t cond;
} share_t;
/*链表的尾部插入 -- 代表入队的操作*/
void insert_at_end(link_list_t **pphead, elem_t data) {
  if (pphead == NULL)
    return;
  // 定义一个新的结点
  link_list_t *new_node = (link_list_t *)malloc(sizeof(link_list_t));
  if (new_node == NULL) {
    printf("malloc failed!\n");
    return;
  }
  new_node->data = data;
  new_node->next = NULL;
  // 若链表无数据元素
  if (*pphead == NULL) {
    *pphead = new_node;
    return;
  }
  // 若链表至少一个数据元素
  link_list_t *tail = *pphead;
  while (tail->next != NULL) {
    tail = tail->next;
  }
  // 插入新的结点
  tail->next = new_node;
  return;
}
/*链表的头部删除 -- 代表出队的操作*/
void delete_from_beginning(link_list_t **pphead) {
  if (pphead == NULL || *pphead == NULL) {
    return;
  }
  // 此时链表中至少一个结点
  // 使用cur指针保存当前头部结点的地址
  link_list_t *cur = *pphead;
  // 将*pphead指向头部结点的下一个结点
  *pphead = (*pphead)->next;
  // 释放头部结点
  free(cur);
  return;
}
void print_link_list(link_list_t *head) {
  if (head == NULL)
    return;
  while (head) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

// 生产者 -- 用于生产数据
// 生产者分为两个步骤
// 1.何时才开始生产数据,不生产数据的时候要干嘛 ->等待
// 2.开始生产数据 -- 发送信号
void *thread_producer(void *arg) {
  char *name = "producer";
  share_t *resource = (share_t *)arg;
  while (1) {
    // 假设count > 20时,就停止生产数据,等待
    pthread_mutex_lock(&resource->mutex);
    if (resource->count > 20) {
      printf("%s:I stop to produce\n", name);
      pthread_cond_wait(&resource->cond, &resource->mutex);
    }
    // 开始生产数据,将新结点入队
    insert_at_end(&resource->phead, 22);
    // 每生产一个数据,将count加1
    resource->count++;
    printf("%s:one production is complete,count is %d\n", name,
           resource->count);
    print_link_list(resource->phead);
    pthread_cond_signal(&resource->cond);
    pthread_mutex_unlock(&resource->mutex);
  }
  pthread_exit(NULL);
}
void *thread_consumer(void *arg) {
  share_t *resource = (share_t *)arg;
  char *name = "consumer";
  while (1) {
    // 当count == 0时,就停止消费,等待
    pthread_mutex_lock(&resource->mutex);
    if (resource->count == 0) {
      printf("%s:I stop consume\n", name);
      pthread_cond_wait(&resource->cond, &resource->mutex);
    }
    // 开始消费,出队
    for (int i = 0; i < 5; i++) {
      delete_from_beginning(&resource->phead);
      resource->count--;
    }
    printf("%s:five consume is complete,count is %d\n", name, resource->count);
    print_link_list(resource->phead);
    pthread_cond_signal(&resource->cond);
    pthread_mutex_unlock(&resource->mutex);
    sleep(1);
  }
  pthread_exit(NULL);
}
int main() {
  // 定义并初始化共享数据
  share_t resource;
  resource.phead = NULL;
  resource.count = 0;
  pthread_mutex_init(&resource.mutex, NULL);
  pthread_cond_init(&resource.cond, NULL);
  // 创建2个线程,一个作为生产者,一个作为消费者
  pthread_t th[2];
  for (int i = 0; i < 2; i++) {
    if (0 == i) {
      // 作为生产者
      if (pthread_create(&th[i], NULL, thread_producer, (void *)&resource) != 0)
        return 1;
    } else {
      // 作为消费者
      if (pthread_create(&th[i], NULL, thread_consumer, (void *)&resource) != 0)
        return 1;
    }
  }
  for (int i = 0; i < 2; i++) {
    if (pthread_join(th[i], NULL) != 0)
      return 1;
  }
  pthread_mutex_destroy(&resource.mutex);
  pthread_cond_destroy(&resource.cond);
  return EXIT_SUCCESS;
}
