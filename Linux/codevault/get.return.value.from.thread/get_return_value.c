// 获取子线程的返回值
#include <tytofu.h>

// 多个线程执行的函数 -- 获取一个随机值
void *routine(void *arg) {
  // 存储在.data,.bss中的对象必须是在编译时确定
  //  static int value = (rand() % 6) + 1; // 获取1-6之间的随机值
  //  获取1-6之间的随机值
  int *value = malloc(sizeof(int));
  if (NULL == value) {
    printf("malloc failed!\n  ");
    return NULL;
  }
  *value = (rand() % 6) + 1;
  return value;
}
int main(int argc, char *argv[]) {
  // 创建多个线程
  pthread_t th[6];
  // 获取多个线程的退出信息
  int *res[6] = {0};
  srand(time(NULL));
  int length = sizeof(th) / sizeof(pthread_t);
  for (int i = 0; i < length; i++) {
    if (pthread_create(th + i, NULL, routine, NULL) != 0)
      return 1;
  }
  for (int i = 0; i < 6; i++) {
    if (pthread_join(th[i], (void **)(res + i)) != 0) {
      return 1;
    }
  }

  // 获取各个线程的返回值,并释放资源
  for (int i = 0; i < 6; i++) {
    printf("th[%d] is %d\n", i, *(*(res + i)));
    free(res[i]);
  }
  return EXIT_SUCCESS;
}
