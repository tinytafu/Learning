#include <complex.h>
#include <tytofu.h>

// 共享资源
int fuel = 0;
// fuel的互斥体
pthread_mutex_t fuel_mutex;
// 加油
void *fuel_filling(void *arg) {
  sleep(1);
  // 每次加油加五次,每一次加15
  for (int i = 0; i < 5; i++) {
    // 上锁
    pthread_mutex_lock(&fuel_mutex);
    fuel += 15;
    printf("filled fuel... %d\n", fuel);
    // 解锁
    pthread_mutex_unlock(&fuel_mutex);
  }
  return NULL;
}
// 汽车消耗油
void *car(void *arg) {
  pthread_mutex_lock(&fuel_mutex);
  while (fuel < 40) {
    printf("no fuel...\n");
    sleep(1);
  }
  fuel -= 40;
  printf("Got fuel.Now left:%d\n", fuel);
  pthread_mutex_unlock(&fuel_mutex);
  return NULL;
}
int main() {
  // 初始化fuel的互斥体
  pthread_mutex_init(&fuel_mutex, NULL);
  pthread_t th[2];
  // 创建两个线程
  for (int i = 0; i < 2; i++) {
    if (1 == i) {
      if (pthread_create(&th[i], NULL, car, NULL) != 0) {
        return 1;
      }
    } else {
      if (pthread_create(&th[i], NULL, fuel_filling, NULL) != 0) {
        return 2;
      }
    }
  }
  for (int i = 0; i < 2; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 2;
    }
  }
  // 销毁互斥体
  pthread_mutex_destroy(&fuel_mutex);
  return EXIT_SUCCESS;
}
