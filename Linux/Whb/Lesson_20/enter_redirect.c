// 输入重定向
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  umask(000);
  // 前提是文件存在
  int fd = open("log.txt", O_RDONLY);
  if (fd < 0) {
    perror("open");
    exit(-1);
  }

  close(0);
  dup2(fd, 0);
  char buf[1024];
  char line[50];
  int cnt = 1;
  while (fgets(line, sizeof(line) - 1, stdin) != NULL) {
    if (cnt == 1)
      strncpy(buf, line, sizeof(line) - 1);
    else
      strcat(buf, line);
    cnt++;
  }
  printf("%s", buf);
}
