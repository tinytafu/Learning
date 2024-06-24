#include <tytofu.h>

int global = 20;
void *thread_start(void *arg) {
  printf("child thread,my pid is %d\n", getpid());
  global++;
  printf("global is %d\n", global);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t tid;
  // 创建子线程
  pthread_create(&tid, NULL, thread_start, NULL);
  // 等待子线程退出
  pthread_join(tid, NULL);
  printf("main thread,my pid is %d\n", getpid());
  printf("global is %d\n", global);
  return EXIT_SUCCESS;
}
