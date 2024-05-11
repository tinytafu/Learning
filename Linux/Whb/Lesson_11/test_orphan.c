//测试孤儿进程被那个进程领养
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main () {
  //创建一个进程
  pid_t pid = fork();
  if(pid == 0) {
    while (1) {
      printf("我是子进程: %d\n",getpid());
      sleep(1);
    }
  }else {
    int cnt = 10;
    while (cnt) {
      printf("我是父进程: %d,我执行%ds后退出\n",getppid(),cnt--);
      sleep(1);
    }
    exit(0);
  }
}
