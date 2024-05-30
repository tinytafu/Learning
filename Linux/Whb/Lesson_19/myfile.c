#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  // 设置umask
  umask(0);
  // 将文件描述符为0的文件对象关闭 -- stdin
  close(1);
  // 打开一个文件
  int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (fd < 0) {
    perror("open");
    exit(-1);
  }

  printf("fd:%d", fd);
  fflush(stdout);
}
