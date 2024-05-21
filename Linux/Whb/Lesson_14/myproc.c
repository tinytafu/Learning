#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
  pid_t pid = fork();
  
  if(0 == pid) {
    while(1){
      printf("我是子进程,我现在正在运行!pid = %d\n",getpid());
      // int *pointer;
      // *pointer = 10;
      // printf("我没执行");
    }
  }else {
    //保存进程退出信息
    int status = 0;
    printf("我准备等待子进程了,注意查看现象\n");
    // pid_t ret = wait(&status);
    pid_t ret = waitpid(pid, &status, 0);
    if(0 > ret ) {
      printf("等待失败!");
    }else {
      printf("waitpid等待成功,等待成功的子进程pid = %d,子进程的退出状态码exit_code = %d,子进程的退出信号是%d\n",ret,(status >> 8)&0xFF,status & 0x7F);
    }
  }
}

// void fun () {
//   printf("我要终止了!\n");
//   exit(12);
// }
// int main () {
//
//   printf("hello");
//   sleep(1);
//   // exit(0);
//   _exit(0);
//   // fun();
//
//   return 0;
  // for (int i = 0;i < 100;i++) {
  //   printf("%d: %s\n",i,strerror(i));
  // }

  // pid_t pid;
  //
  // printf("Before: pid is %d\n",getpid());
  // if ((pid = fork()) == -1){
  //   perror("fork()");
  //   exit(1);
  // }
  // printf("After:pid is %d,fork return %d\n",getpid(),pid);
  // sleep(1);
  // pid_t id = fork();
  //
  // if(0 == id) {
  //   while(1) {
  //     printf("我是子进程,pid = %d,ppid = %d\n",getpid(),getppid());
  //     sleep(1);
  //   }
  // }else {
  //   while(1) {
  //     printf("我是父进程,pid = %d,ppid = %d\n",getpid(),getppid());
  //     sleep(1);
  //   }
  // }
