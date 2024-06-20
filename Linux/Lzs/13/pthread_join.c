// 多线程程序
#include <tytofu.h>

// 子线程的执行序列
static void *thread_start(void *arg) {
  printf("i am child thread\n");
  while (1)
    sleep(1);
  return NULL;
}
int main(int argc, char *argv[]) {
  // 获取子线程的id
  pthread_t tid;
  // 创建一个子线程
  pthread_create(&tid, NULL, thread_start, NULL);
  printf("i am main thread\n");
  // 等待子线程结束
  if ((pthread_join(tid, NULL)) != 0) {
    fprintf(stderr, "Error joining thread\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
