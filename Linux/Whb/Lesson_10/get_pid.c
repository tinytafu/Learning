#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  /*当前程序被加载到内存,程序在内存中的数据与描述进程的pcb(task_struct)关联
   起来成为进程.log.txt所在的当前路径指的就是进程当前工作路径(cwd)
   大白话就是这个程序在那路径下加载到内存与pcb关联,那么这个路径就是当前进程工作路径*/
  FILE *file = fopen("log.txt", "w");
  while (1) {
    // 获取当前进程的pid --> process id
    printf("pid of this process is %d\n", getpid());
    sleep(1);
  }
}
