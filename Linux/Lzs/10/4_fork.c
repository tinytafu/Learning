#include <tytofu.h>
#include <unistd.h>

int main() {
  switch (fork()) {
  case -1: {
    exit(EXIT_FAILURE);
    break;
  }
  case 0: {
    printf("i am child,my pid is %d,my parent pid is %d\n", getpid(),
           getppid());
    break;
  }
  default: {
    // 目的是先让子进程执行
    sleep(1);
    printf("i am parent,my pid is %d,my parent pid is %d\n", getpid(),
           getppid());
  }
  }
}
