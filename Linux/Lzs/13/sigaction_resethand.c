// 注册一次,递送一次
#include <signal.h>
#include <tytofu.h>
void handler(int signum) {
  printf("Before:signum is %d\n", signum);
  sleep(5);
  printf("Before:signum is %d\n", signum);
}
int main(int argc, char *argv[]) {
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = handler;
  // 注册一次,递送一次,重启低速系统调用
  act.sa_flags = SA_RESTART | SA_RESETHAND;
  // 注册信号
  sigaction(SIGINT, &act, NULL);
  char buf[1024] = {0};
  ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
  buf[rret - 1] = '\0';
  printf("buf is %s\n", buf);
  return EXIT_SUCCESS;
}
