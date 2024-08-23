// calloc内存分配函数
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int x;
  int y;
} node_t;
int main() {
  int *str = (int *)calloc(2, sizeof(int));
  for (int i = 0; i < 2; i++) {
    printf("%d\n", str[i]);
  }
  free(str);
  str = NULL;

  // 申请一个结构体数组
  node_t *str_node = (node_t *)calloc(3, sizeof(node_t));

  // 申请一个结构体对象
  node_t *node = (node_t *)calloc(1, sizeof(node_t));

  free(str_node);
  str_node = NULL;
  free(node);
  node = NULL;
}
