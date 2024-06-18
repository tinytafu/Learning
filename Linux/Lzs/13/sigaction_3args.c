// 三个参数的handler
#include <signal.h>
#include <string.h>
#include <tytofu.h>
void handler(int signum, siginfo_t *siginfo, void *P) {
  printf("signum is %d,uid = %d\n", signum, siginfo->si_uid);
}
int main(int argc, char *argv[]) {
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  // 1.设置sa_flags
  act.sa_flags = SA_RESTART | SA_SIGINFO;
  // 2.设置handler
  act.sa_sigaction = handler;
  sigaction(SIGINT, &act, NULL);
  sigaction(SIGQUIT, &act, NULL);
  char buf[1024] = {0};
  ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
  ERROR_CHECK(rret, -1, "read");
  return EXIT_SUCCESS;
}
