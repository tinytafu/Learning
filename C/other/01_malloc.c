// malloc库函数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARR_LEN 10
typedef struct student {
  char name[64];
  int age;
} stu_t;
int main() {
  stu_t *s1 = (stu_t *)malloc(sizeof(stu_t));
  strncpy(s1->name, "wangshuai", sizeof(s1->name) - 1);
  s1->name[strlen(s1->name)] = '\0';
  printf("s1->name is %s\n sizeof(s1->name) - 1 is %zu\n", s1->name,
         sizeof(s1->name) - 1);
  // 1.使用malloc函数申请若干字节的堆内存
  int *dyn_arr = (int *)malloc(sizeof(int) * ARR_LEN);
  // 2.判断是否申请成功
  if (dyn_arr == NULL) {
    printf("error:malloc allocation failed.\n");
    return -1;
  }
  // 3.malloc不会为已分配的堆内存进行初始化
  int *tmp = dyn_arr;
  for (int i = 0; i < ARR_LEN; i++) {
    *tmp++ = i;
  }
  for (int i = 0; i < ARR_LEN; i++) {
    dyn_arr[i] = i;
  }
  for (int i = 0; i < ARR_LEN; i++) {
    *(dyn_arr + i) = i;
  }
  // 4.释放堆内存,防止内存泄露
  free(dyn_arr);
  // 5.防止double free
  dyn_arr = NULL;
}
