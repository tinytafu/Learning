// alarm是从当前的多少秒之后发送SIGAALRM信号
#include <tytofu.h>
void handler(int signum) {
  printf("signum is %d\n", signum);
  time_t now = time(NULL);
  printf("now is %s\n", ctime(&now));
}

int main(int argc, char *argv[]) {
  signal(SIGALRM, handler);

  // alarm 10秒之后开始递送SIGALRM
  alarm(10);
  handler(0);
  while (1) {
    sleep(1);
  }
  return EXIT_SUCCESS;
}
