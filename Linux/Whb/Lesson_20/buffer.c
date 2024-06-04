// 缓冲区
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("hello printf ");
  fprintf(stdout, "hello fprintf ");
  fputs("hello fputs ", stdout);

  write(1, "hello write ", strlen("hello write"));
  sleep(5);

  close(stdout->_fileno);
}
