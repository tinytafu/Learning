// 使用两个线程分别计算数组的前半部分和后半部分的数值和,最后由main线程计算总和
#include <tytofu.h>

int prims[6] = {2, 3, 5, 7, 11, 13};

void *routine(void *arg) {
  int index = *(int *)arg;
  int sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += prims[index + i];
  }
  printf("sum is %d\n", sum);
  *(int *)arg = sum;
  return arg;
}

int main(int argc, char *argv[]) {
  pthread_t th[2];
  // 创建两个线程,一个线程传递数组第0个索引,一个线程传递第3个索引
  for (int i = 0; i < 2; i++) {
    int *a = malloc(sizeof(int));
    *a = i * 3;
    if (pthread_create(&th[i], NULL, routine, a) != 0) {
      return 1;
    }
  }

  int global_sum = 0;
  for (int i = 0; i < 2; i++) {
    int *res = NULL;
    if (pthread_join(th[i], (void **)&res) != 0) {
      return 1;
    }
    global_sum += *res;
    free(res);
  }
  printf("global_sum is %d\n", global_sum);
  return EXIT_SUCCESS;
}
