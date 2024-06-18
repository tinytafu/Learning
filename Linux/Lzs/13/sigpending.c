// 检查某个信号是否在penging集合中
#include <tytofu.h>
void handler(int signum) {
  printf("Before:signum is %d\n", signum);
  sleep(2);
  printf("After:signum is %d\n", signum);
  sigset_t set;
  sigpending(&set);
  // 判断SIGINT信号是否在pending集合中
  if (sigismember(&set, SIGINT)) {
    printf("SIGINT is in pending\n");
  } else
    printf("SIGINT is not in pending\n");
}
int main(int argc, char *argv[]) {
  // 注册信号
  signal(SIGINT, handler);
  while (1) {
    sleep(1);
  }
  return EXIT_SUCCESS;
}
