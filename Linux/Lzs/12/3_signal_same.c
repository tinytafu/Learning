#include <tytofu.h>
void handler(int signum) {
  printf("before signum is %d\n", signum);
  // 递送信号递送的慢一点
  sleep(5);
  printf("after signum is %d\n", signum);
}

int main() {
  // 注册信号
  signal(SIGINT, handler);
  while (1) {
    sleep(1);
  }
}
