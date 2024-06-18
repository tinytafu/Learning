// 注册不同的信号为同一个递送行为
#include <tytofu.h>

void handler(int signum) {
  printf("Before:signum is %d\n", signum);
  // 信号递送的慢一些,观察现象
  sleep(5);
  printf("After:signum is %d\n", signum);
}

int main() {
  // 注册SIGINT信号
  signal(SIGINT, handler);
  // 注册SIGQUIT
  signal(SIGQUIT, handler);
  while (1) {
    sleep(1);
  }
}
