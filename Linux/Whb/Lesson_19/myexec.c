#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  umask(0);
  // 打开一个文件,如果不存在则创建
  // int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
  int fd = open("log.txt", O_RDONLY);
  if (fd < 0) {
    perror("open");
    exit(-1);
  }
  // 存储读取数据
  char buf[1024];
  ssize_t ret = read(fd, buf, sizeof(buf) - 1);
  if (ret > 0) {
    buf[ret] = '\0';
    printf("%s", buf);
  }
  // const char *msg = "wangshuai\n";
  // for (int i = 0; i < 2; i++) {
  //   write(fd, msg, strlen(msg));
  // }
  close(fd);
}
