// 打开管道读端
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf 1.pipe
  ARGS_CHECK(argc, 2);
  /*打开管道文件*/
  int fd = open(argv[1], O_RDONLY);
  ERROR_CHECK(fd, -1, "open");

  char buf[1024] = {0};
  ssize_t sret = read(fd, buf, sizeof(buf));
  ERROR_CHECK(sret, -1, "read");
  printf("sret is %ld\nbuf is %s\n", sret, buf);
  close(fd);
}
