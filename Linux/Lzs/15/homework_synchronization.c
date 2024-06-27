// 两个线程A和B实现简单的同步
#include <tytofu.h>

int flag = 0;
pthread_mutex_t flag_mutex;
void *threadA(void *arg) {
  char *ch = (char *)arg;
  for (int i = 0; i < 10; i++) {
    pthread_mutex_lock(&flag_mutex);
    flag++;
    printf("%c:flag is %d\n", *ch, flag);
    pthread_mutex_unlock(&flag_mutex);
    sleep(2);
  }
  return NULL;
}

void *threadB(void *arg) {
  char *ch = (char *)arg;
  while (1) {
    pthread_mutex_lock(&flag_mutex);
    if (flag < 10) {
      printf("%c:waiting...\n", *ch);
      pthread_mutex_unlock(&flag_mutex);
      sleep(3);
    } else {
      printf("%c:waiting end!\n", *ch);
      break;
    }
  }
  printf("%c:flag is %d\n", *ch, flag);
  flag--;
  pthread_mutex_unlock(&flag_mutex);
  return NULL;
}

int main(int argc, char *argv[]) {
  // 初始化互斥锁
  pthread_mutex_init(&flag_mutex, NULL);
  pthread_t th[2];
  for (int i = 0; i < 2; i++) {
    if (0 == i) {
      char *ch = (char *)malloc(sizeof(char));
      if (NULL == ch) {
        printf("malloc failed\n");
        return 1;
      }
      *ch = 'A';
      if (pthread_create(&th[i], NULL, threadA, (void *)ch) != 0) {
        return 2;
      }
    } else {
      char *ch = (char *)malloc(sizeof(char));
      if (NULL == ch) {
        printf("mallco failed\n");
        return 1;
      }
      *ch = 'B';
      if (pthread_create(&th[i], NULL, threadB, (void *)ch) != 0) {
        return 2;
      }
    }
  }
  // 等待两个线程执行完毕
  for (int i = 0; i < 2; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 2;
    }
  }
  // 销毁互斥锁
  pthread_mutex_destroy(&flag_mutex);
  return EXIT_SUCCESS;
}
