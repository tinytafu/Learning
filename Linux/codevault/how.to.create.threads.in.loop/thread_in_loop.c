#include <tytofu.h>

int global = 0;
pthread_mutex_t mutex;
void *routine(void *arg) {
  for (int i = 0; i < 20000; i++) {
    // 上锁
    pthread_mutex_lock(&mutex);
    global++;
    // 解锁
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
int main(int argc, char *argv[]) {
  pthread_t th[6];
  // 循环创建线程
  for (int i = 0; i < 6; i++) {
    if (pthread_create(th + i, NULL, routine, NULL) != 0)
      return 1;
  }
  // 循环等待线程--等待线程完成的顺序不代表线程执行完的循序
  for (int i = 0; i < 6; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 2;
    }
  }
  return EXIT_SUCCESS;
}
