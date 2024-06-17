// 写时拷贝cow
#include <stdio.h>
#include <tytofu.h>

int global_val = 10;
static short static_val;
int main() {
  int local_val = 10;
  int *pheap = calloc(1, sizeof(int));
  switch (fork()) {
  case -1: {
    perror("fork");
    break;
  }
  case 0: {
    global_val = 200;
    static_val = 201;
    local_val = 202;
    *pheap = 203;
    printf("i am child,global_val is %d,static_val is %d,local_val is "
           "%d,*pheap is %d\n",
           global_val, static_val, local_val, *pheap);
    break;
  }
  default: {
    global_val = 101;
    static_val = 102;
    local_val = 103;
    *pheap = 100;
    printf("i am parent,global_val is %d,static_val is %d,local_val is "
           "%d,*pheap is %d\n",
           global_val, static_val, local_val, *pheap);
    break;
  }
  }
}
