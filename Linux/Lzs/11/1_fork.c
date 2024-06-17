#include <tytofu.h>

int main() {
  switch (fork()) {
  case -1:
    perror("fork");
    break;
  case 0: {
    printf("i am child,my pid is %d,ppid is %d\n", getpid(), getppid());
    _exit(0);
  }
  default: {
    wait(NULL);
    printf("i am parent,my pid is %d,ppid is %d\n", getpid(), getppid());
    exit(0);
  }
  }
}
