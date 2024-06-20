#include <tytofu.h>

void sigalrm_handler(int signum) {
  time_t now = time(NULL);
  printf("now is %s\n", ctime(&now));
}
int main(int argc, char *argv[]) {
  // 注册信号
  // signal(SIGALRM, sigalrm_handler);
  signal(SIGVTALRM, sigalrm_handler);
  // 创建setitimer中第个参数的对象
  struct itimerval timer;
  // 设置从当前起等待的时间
  timer.it_value.tv_sec = 3;
  timer.it_value.tv_usec = 0;
  // 设置当定时器结束等待时间之后每间隔多少秒生成一个信号
  timer.it_interval.tv_sec = 2;
  timer.it_interval.tv_usec = 0;
  // 设置时间
  // setitimer(ITIMER_REAL, &timer, NULL);
  setitimer(ITIMER_VIRTUAL, &timer, NULL);
  // 记录当前时间
  sigalrm_handler(0);
  while (1) {
  }
  return EXIT_SUCCESS;
}
