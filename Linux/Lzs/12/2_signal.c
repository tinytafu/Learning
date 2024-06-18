#include <tytofu.h>

// SIGINT信号的自定义行为
void handler(int signum) { printf("signum is %d\n", signum); }

int main() {
  sleep(5);
  printf("sleep over\n");
  // 注册信号 -- 更改信号的递送行为
  signal(SIGINT, handler);
  // 让当前进程保持继续运行
  while (1) {
    sleep(1);
  }
}
