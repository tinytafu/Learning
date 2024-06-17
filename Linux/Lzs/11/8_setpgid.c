// 重新使用一个进程创建一个进程组,一个进程组的组长是不可以进行换组的
#include <tytofu.h>

int main() {
  pid_t pid = fork();
  if (0 == pid) {
    printf("i am child,pid = %d,ppid = %d,pgid = %d,pgid of ppid = %d\n",
           getpid(), getppid(), getpgid(0), getpgid(getppid()));
    // 创建进程组
    int ret = setpgid(0, 0);
    ERROR_CHECK(ret, -1, "setpgid");
    printf("i am child,pid = %d,ppid = %d,pgid = %d,pgid of ppid = %d\n",
           getpid(), getppid(), getpgid(0), getpgid(getppid()));
    _exit(0);
  }
  int status = 0;
  pid_t ret = waitpid(pid, &status, 0);
  if (ret < 0)
    perror("waitpid");
  if (WIFEXITED(status))
    printf("exit code is %d\n", WEXITSTATUS(status));
  exit(0);
}
