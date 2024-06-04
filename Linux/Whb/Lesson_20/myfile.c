#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  umask(0);
  // 打开一个文件
  int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
  // 利用fprintf实现追加重定向将stdout先关闭
  close(1);
  dup2(fd, 1);

  fprintf(stdout, "我是王帅,我在做追加重定向! fd = %d\n", fd);
}
