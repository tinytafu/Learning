#include <tytofu.h>

int main() {
  pid_t pid = fork();
  if (0 == pid) {
    printf("i am child,pid is %d,ppid is %d\n", getpid(), getppid());
    _exit(0);
  }
  int status = 0;
  pid_t ret = waitpid(pid, &status, 0);
  if (ret < 0)
    perror("waitpid");
  if (WIFEXITED(status))
    printf("exit code is %d\n", WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    printf("exit signale is %d\n", WTERMSIG(status));
  exit(0);
}
