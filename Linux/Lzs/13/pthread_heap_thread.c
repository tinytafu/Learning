// 一个线程访问访问另外一个线程的堆资源,很有可能在另外一个线程还没进行访问的时候,这个线程的堆资源已经被释放

#include <tytofu.h>

static void *thread_start(void *arg) {
  int *p = (int *)arg;
  printf("*p is %d\n", *p);
  return NULL;
}
int main(int argc, char *argv[]) {
  int *p = (int *)malloc(sizeof(int));
  if (NULL == p) {
    printf("malloc failed\n");
    return -1;
  }
  *p = 100;
  pthread_t tid;
  pthread_create(&tid, NULL, thread_start, p);
  // free(p);
  sleep(2);
  return EXIT_SUCCESS;
}
