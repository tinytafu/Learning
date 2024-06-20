// 多个线程访问某个线程申请的堆内存资源
#include <tytofu.h>

static void *thread_start(void *arg) {
  // 对参数进行转换
  int *p = (int *)arg;
  printf("*p is %d\n", *p);
  return NULL;
}

int main(int argc, char *argv[]) {
  // 申请一份堆资源
  int *heap = (int *)calloc(1, sizeof(int));
  if (NULL == heap) {
    printf("alloc failed\n");
    return -1;
  }
  *heap = 100;
  pthread_t tid;
  // 创建一个子线程
  pthread_create(&tid, NULL, thread_start, heap);
  free(heap);
  pthread_join(tid, NULL);
  return EXIT_SUCCESS;
}
