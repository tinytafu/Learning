// 一个线程访问访问另外一个线程的堆栈,很有可能在另外一个线程还没进行访问的时候,这个线程的对栈
// 已经被销毁了

#include <tytofu.h>

static void *thread_start(void *arg) {
  int *p = (int *)arg;
  printf("*p is %d\n", *p);
  return NULL;
}
static void *thread_start_one(void *arg) {
  int i = 10;
  pthread_t tid;
  pthread_create(&tid, NULL, thread_start, &i);
  return NULL;
}
int main(int argc, char *argv[]) {
  pthread_t tid;
  pthread_create(&tid, NULL, thread_start_one, NULL);
  sleep(2);
  return EXIT_SUCCESS;
}
