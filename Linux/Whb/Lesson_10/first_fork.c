// first use fork

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t id = fork();
  // 第一个问题:为何同一个id打印出两个不同的值?
  printf("hello fork: %d\n", id);
  // 第二个问题:在C语言中是否if与else都执行,两个while死循环会同时执行吗?
  if (id == 0) {
    while (1) {
      printf("I'm child process:\t%d,my parent process:\t%d\n", getpid(),
             getppid());
      sleep(1);
    }
  } else {
    while (1) {
      printf("I'm parent process:\t%d,my perent process:\t%d\n", getpid(),
             getppid());
      sleep(1);
    }
  }
}
