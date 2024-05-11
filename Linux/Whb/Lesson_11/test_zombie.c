//测试僵尸进程显示状态
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main () {
  //创建一个进程
  pid_t pid = fork();
  if(pid == 0) {
    int cnt = 5;
    while (cnt) {
      printf("我是子进程,我执行%ds就退出了\n",cnt--);
      sleep(1);
    }
  exit(0);
  }else {
    while (1) {
      printf("我是父进程\n");
      sleep(1);
    }
  }
}
