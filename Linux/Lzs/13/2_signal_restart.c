// signal会重启低速系统调用
#include <tytofu.h>

void handler(int signum) {
  printf("Before:signum is %d\n", signum);
  sleep(5);
  printf("After:signum is %d\n", signum);
}
int main() {
  // 注册信号
  signal(SIGINT, handler);
  char buf[1024] = {0};
  ssize_t rret = read(STDIN_FILENO, buf, sizeof buf);
  ERROR_CHECK(rret, -1, "read");
  printf("buf is %s\n", buf);
  return EXIT_SUCCESS;
}
