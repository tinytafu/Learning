#include <tytofu.h>

// 创建一个互斥体
pthread_mutex_t mutex;

void *routine(void *arg) {
  // 使用trlock,若上锁,则返回0,不上锁则返回其他数值
  if (pthread_mutex_trylock(&mutex) == 0) {
    printf("Gte lock\n");
    pthread_mutex_unlock(&mutex);
  } else { // 若没上锁,则做其他事情
    printf("Not lock\n");
  }
  return NULL;
}
int main(int argc, char *argv[]) {
  // 初始化互斥体
  pthread_mutex_init(&mutex, NULL);
  pthread_t th[4];
  for (int i = 0; i < 4; i++) {
    if (pthread_create(&th[i], NULL, routine, NULL) != 0) {
      return 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 1;
    }
  }
  // 销毁一个互斥体
  pthread_mutex_destroy(&mutex);
  return EXIT_SUCCESS;
}
