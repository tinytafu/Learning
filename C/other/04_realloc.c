// 正确使用realloc的演示代码
#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int len) {
  printf("[");
  for (int i = 0; i < len; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\b\b]\n");
}

int main() {
  int size = 5;
  int *str = (int *)calloc(size, sizeof(int));
  if (NULL == str) {
    printf("error:calloc failed!\n");
    exit(-1);
  }
  // 打印一下数组元素
  print_arr(str, size);

  // 重分配缩减
  int new_size = 3;
  // 创建临时指针存储realloc的返回值
  int *tmp = realloc(str, sizeof(int) * new_size);
  if (NULL == tmp) {
    printf("realloc failed!\n");
    exit(-1);
  }
  str = tmp;
  print_arr(str, new_size);

  // 重分配扩容
  int new_size2 = 10;
  int *tmp2 = realloc(str, new_size2 * sizeof(int));
  if (NULL == tmp2) {
    printf("realloc failed!\n");
    exit(-1);
  }
  str = tmp2;
  // 扩展的内存单元中存储的都是随机值

  // 创建一个临时指针存储原来str中最后一个有效数据的地址值
  int *p = str + new_size; // 缩减后是原来的str
  while (p < (str + new_size2)) {
    *p++ = 8;
  }
  print_arr(str, new_size2);
  free(str);
}
