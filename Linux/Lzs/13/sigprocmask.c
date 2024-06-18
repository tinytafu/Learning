// 对某个信号不进行临时屏蔽,实现全程屏蔽,那么在发送信号的时候,这个时候会加入到
// pending集合中,使用sigpending查看
#include <tytofu.h>

void handler(int signum) {
  printf("Before:signum is %d\n", signum);
  sleep(1);
  printf("After:signum is %d\n", signum);
}
int main(int argc, char *argv[]) {
  // 注册信号
  signal(SIGINT, handler);
  sigset_t set;
  // 清空集合
  sigemptyset(&set);
  // 将SIGINT信号加入set
  sigaddset(&set, SIGINT);
  // 调用sigprocmask全程屏蔽set集合中的信号
  sigprocmask(SIG_BLOCK, &set, NULL);
  sleep(10);

  // 设置pending集合
  // 当我递送第一个SIGINT时,就直接不递送,加入pending,因为是全程屏蔽的
  sigset_t pending;
  sigpending(&pending);
  if (sigismember(&pending, SIGINT)) {
    printf("SIGINT is in pending\n");
  } else
    printf("SIGINT is in not pending\n");
  sigprocmask(SIG_UNBLOCK, &set, NULL);
  sleep(1);
  return EXIT_SUCCESS;
}
