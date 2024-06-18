// 阻塞进程,直到给进程发送任何一个信号
#include <tytofu.h>

void handler(int signum) { printf("signum is %d\n", signum); }
int main(int argc, char *argv[]) {
  signal(SIGALRM, handler);
  alarm(10);
  pause();
  return EXIT_SUCCESS;
}
