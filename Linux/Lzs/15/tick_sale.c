// 线程A和B作为买票窗口,而C作为加票窗口,当票数小于10的时候,进行加10张票

#include <tytofu.h>

// 共享资源 -- 票价
typedef struct share {
  // 票的个数
  int ticket;
  // 互斥锁
  pthread_mutex_t mutex;
  // 条件变量
  pthread_cond_t cond_var;
} share_t;
// 定义共享资源
share_t resource;

// 卖票
void *thread_sale(void *arg) {
  char *name = (char *)arg;
  // 先是一直卖票,直到票数为0时,则结束卖票
  while (1) {
    pthread_mutex_lock(&resource.mutex);
    if (resource.ticket == 0) {
      // 解锁,终止循环
      printf("%s:ticket is %d,end\n", name, resource.ticket);
      pthread_mutex_unlock(&resource.mutex);
      break;
    } else if (resource.ticket == 10) {
      printf("%s:I need add ticket\n", name);
      pthread_cond_signal(&resource.cond_var);
      pthread_mutex_unlock(&resource.mutex);
      sleep(1);
    }
    resource.ticket--;
    printf("%s:one ticket is sale,remain %d\n", name, resource.ticket);
    pthread_mutex_unlock(&resource.mutex);
    sleep(1);
  }
  pthread_exit(NULL);
}
// 加票
void *thread_add(void *arg) {
  char *name = (char *)arg;
  // 我只加一次票
  pthread_mutex_lock(&resource.mutex);
  if (resource.ticket > 10) {
    printf("%s:ticket is greater than 10,ticket is %d\n", name,
           resource.ticket);
    pthread_cond_wait(&resource.cond_var, &resource.mutex);
  }
  resource.ticket += 10;
  printf("%s:I have added,ticket is %d\n", name, resource.ticket);
  pthread_mutex_unlock(&resource.mutex);
  pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
  // 初始化共享资源
  resource.ticket = 20;
  pthread_mutex_init(&resource.mutex, NULL);
  pthread_cond_init(&resource.cond_var, NULL);
  // 创建三个线程
  pthread_t th[2];
  for (int i = 0; i < 2; i++) {
    if (1 == i) {
      char *string = "add";
      if (pthread_create(&th[i], NULL, thread_add, (void *)string) != 0) {
        return 1;
      }
    } else if (0 == i) {
      char *string = "window_one";
      if (pthread_create(&th[i], NULL, thread_sale, (void *)string) != 0) {
        return 1;
      }
    } /*else {
      char *string = "window_two";
      if (pthread_create(&th[i], NULL, thread_sale, (void *)string) != 0) {
        return 1;
      }
    }*/
  }
  // 等待子线程退出
  for (int i = 0; i < 2; i++) {
    if (pthread_join(th[i], NULL) != 0) {
      return 1;
    }
  }
  // 销毁互斥锁
  pthread_mutex_destroy(&resource.mutex);
  pthread_cond_destroy(&resource.cond_var);
  return EXIT_SUCCESS;
}
