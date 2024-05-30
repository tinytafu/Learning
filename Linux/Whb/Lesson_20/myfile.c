#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  /*关闭stdout*/
  umask(0);
  int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
  close(1);
  int ret = dup2(fd, 1);
  // write(1, "我是wangshuai", sizeof("我是wangshuai"));
  fprintf(stdout, "我是wangshuai ret is %d\n", ret);
  close(fd);
}
