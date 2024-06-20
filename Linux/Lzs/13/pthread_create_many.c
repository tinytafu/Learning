// 测试本系统可以创建多少个线程
#include <tytofu.h>
static void *thread_start(void *arg) {
  while (1) {
    sleep(1);
  }
}
int main(int argc, char *argv[]) {
  int cnt = 0;
  while (1) {
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_start, NULL);
    if (ret != 0) {
      fprintf(stderr, "%s:%s\n", "pthread_create", strerror(ret));
      printf("cnt = %d\n", cnt);
      break;
    }
    cnt++;
  }
  return EXIT_SUCCESS;
}
