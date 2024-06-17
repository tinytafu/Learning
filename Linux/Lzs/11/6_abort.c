// 异常退出
#include <stdlib.h>
#include <tytofu.h>

int main() {
  pid_t pid = fork();
  if (0 == pid) {
    abort();
    return -1;
  }
  int status = 0;
  pid_t ret = waitpid(pid, &status, 0);
  if (ret < 0)
    perror("waitpid");
  if (WIFEXITED(status)) {
    printf("exit code is %d\n", WEXITSTATUS(status));
  } else if (WIFSIGNALED(status))
    printf("exit signale is %d\n", WTERMSIG(status));
}
