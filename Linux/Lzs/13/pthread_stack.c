// 多线程程序
#include <tytofu.h>

// 子线程的执行序列
static void *thread_start(void *arg) {
  int *p = (int *)arg;
  printf("child:i is %d\n", *p);
  ++*p;
  return NULL;
}
int main(int argc, char *argv[]) {

  int i = 100;
  // 获取子线程的id
  pthread_t tid;
  // 创建一个子线程
  pthread_create(&tid, NULL, thread_start, &i);
  pthread_join(tid, NULL);
  printf("main:i is %d\n", i);
  return EXIT_SUCCESS;
}
