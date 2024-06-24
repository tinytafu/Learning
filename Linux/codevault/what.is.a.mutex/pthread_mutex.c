#include <tytofu.h>

long global = 0;
pthread_mutex_t mutex;
void *routine(void *arg) {

  for (int i = 0; i < 10000000; i++) {
    // 上锁
    pthread_mutex_lock(&mutex);
    global++;
    //  read global;
    //  increment;
    //  write global
    // 解锁
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}
int main() {
  pthread_t t1, t2;
  // 初始化mutex
  pthread_mutex_init(&mutex, NULL);
  // 创建第一个线程
  if (pthread_create(&t1, NULL, routine, NULL) != 0)
    return 1;
  if (pthread_create(&t2, NULL, routine, NULL) != 0)
    return 1;
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  // 执行完毕后,销毁mutex
  pthread_mutex_destroy(&mutex);
  printf("global is %ld\n", global);
  return EXIT_SUCCESS;
}
