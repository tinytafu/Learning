// 新建会话组,一般是进程组的其他进程新建会话,进程组的组长是不可以创建会话的,因为创建
// 一个新的会话会有一个进程组,这个进程组的id就是这个进程的pid
#include <tytofu.h>

int main() {
  if (fork()) {
    exit(0);
  } else {
    printf("Before,sid is %d,ppid is %d\n", getsid(0), getppid());
    setsid();
    printf("After,sid is %d\n", getsid(0));
    _exit(0);
  }
}
