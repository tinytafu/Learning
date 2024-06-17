#include <tytofu.h>

int main() {
  if (fork()) {
    printf("i am parent,pid = %d,ppid = %d,pgid = %d\n", getpid(), getppid(),
           getpgid(getppid()));
    exit(0);
  } else {
    printf("i am parent,pid = %d,ppid = %d,pgid = %d\n", getpid(), getppid(),
           getpgid(getppid()));
    _exit(0);
  }
}
