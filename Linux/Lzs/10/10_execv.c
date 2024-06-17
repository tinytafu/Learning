// 程序替换 -- execl
#include <tytofu.h>
#include <unistd.h>

int main() {
  printf("you can see me!\n");
  printf("pid = %d\n", getpid());
  // 替换父进程
  char *const arr[] = {(char *)"./add", (char *)"3", (char *)"4", NULL};
  execv("add", arr);
  printf("you can't see me!\n");
}
