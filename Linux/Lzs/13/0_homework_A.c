// 利用fork exec wait exit
#include <stdlib.h>
#include <tytofu.h>

int main(int argc, char *argv[]) {
  ARGS_CHECK(argc, 2);
  if (fork()) {
    int status = 0;
    wait(&status);
    if (WIFEXITED(status))
      printf("exit code is %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
      printf("exit signal is %d\n", WTERMSIG(status));
    exit(0);
  } else {
    // 利用execl执行homework_b
    execl("homework_B", "./homework_B", argv[1], NULL);
    _exit(0);
  }
  return EXIT_SUCCESS;
}
