#include <tytofu.h>

int primes[6] = {2, 3, 5, 7, 11, 13};

void *routine(void *arg) {
  sleep(1);
  int index = *(int *)arg;
  printf("%d ", primes[index]);
  free(arg);
  return NULL;
}
int main(int argc, char *argv[]) {
  pthread_t th[6];
  // 创建6个线程
  for (int i = 0; i < 6; i++) {
    // 传递的是i的地址,但是每次循环过后i的值都会发生变化,且每个线程的执行顺序不同,因此不可以直接
    // 传递i的地址,可以借助动态内存的方式
    int *a = malloc(sizeof(int));
    *a = i;
    if (pthread_create(&th[i], NULL, routine, a) != 0) {
      return 1;
    }
  }
  // 等待线程执行完毕
  for (int i = 0; i < 6; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 1;
    }
  }
  return EXIT_SUCCESS;
}
