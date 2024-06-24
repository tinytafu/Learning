#include <tytofu.h>

int global = 20;
int main() {

  pid_t pid = fork();

  if (0 == pid) {
    global++;
    printf("child pid is %d,global is %d\n", getpid(), global);
    exit(0);
  }
  waitpid(pid, NULL, 0);
  printf("parent pid is %d,global is %d\n", getpid(), global);
  exit(0);
}
