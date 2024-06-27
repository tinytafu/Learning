#include <complex.h>
#include <tytofu.h>

// 共享资源
int fuel = 0;
// fuel的互斥体
pthread_mutex_t fuel_mutex;
// 条件变量
pthread_cond_t cond_fuel;
// 加油
void *fuel_filling(void *arg) {
  // 每次加油加五次,每一次加15
  for (int i = 0; i < 5; i++) {
    // 上锁
    pthread_mutex_lock(&fuel_mutex);
    fuel += 60;
    printf("filled fuel... %d\n", fuel);
    // 解锁
    pthread_mutex_unlock(&fuel_mutex);
    // 每执行一次释放一次信号
    pthread_cond_signal(&cond_fuel);
    sleep(1);
  }
  return NULL;
}
// 汽车消耗油
void *car(void *arg) {
  pthread_mutex_lock(&fuel_mutex);
  while (fuel < 40) { // 条件成立继续往下执行
    printf("no fuel...\n");
    // 等待信号到来,随后执行while中的判断
    pthread_cond_wait(&cond_fuel, &fuel_mutex);
    /*
     *等价于以下三个步骤:
     1.pthread_mutex_unlock(&fuel_mutex)
     2.只有解锁别的线程才能拿到锁,才能释放信号,这边等待信号
     3.等待信号之后,执行pthread_mutex_lock(&fuel_mutex)*/
  }
  fuel -= 40;
  printf("Got fuel.Now left:%d\n", fuel);
  pthread_mutex_unlock(&fuel_mutex);
  return NULL;
}
int main() {
  // 初始化fuel_mutex
  pthread_mutex_init(&fuel_mutex, NULL);
  // 初始化cond_fuel
  pthread_cond_init(&cond_fuel, NULL);
  pthread_t th[5];
  // 创建两个线程
  for (int i = 0; i < 5; i++) {
    if (4 == i) {
      if (pthread_create(&th[i], NULL, fuel_filling, NULL) != 0) {
        return 1;
      }
    } else {
      if (pthread_create(&th[i], NULL, car, NULL) != 0) {
        return 2;
      }
    }
  }
  for (int i = 0; i < 5; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 2;
    }
  }
  // 销毁fuel_mutex
  pthread_mutex_destroy(&fuel_mutex);
  // 销毁cond_fuel
  pthread_cond_destroy(&cond_fuel);
  return EXIT_SUCCESS;
}
