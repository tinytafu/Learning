// 获取当前进程和当前进程的父进程的pid
#include <tytofu.h>

int main() {

  printf(
      "pid of calling process is %d,parent pid of the calling process is %d\n",
      getpid(), getppid());
}
