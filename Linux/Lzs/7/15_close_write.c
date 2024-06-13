// 管道写端
#include <tytofu.h>
int main(int argc, char **argv) {
  // 程序如何执行:tf 1.pipe
  ARGS_CHECK(argc, 2);

  // 打开管道文件写端
  int fd = open(argv[1], O_WRONLY);
  ERROR_CHECK(fd, -1, "open");
  sleep(10);
  /*读端关闭继续写 -- 报错*/
  ssize_t wret = write(fd, "hello wangshuai!\n", strlen("hellowangshuai!\n"));
  ERROR_CHECK(wret, -1, "write");
  printf("hello\n");
  // close(fd);
}
