// 打开管道读端
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf 1.pipe
  ARGS_CHECK(argc, 2);
  /*打开管道文件*/
  int fd = open(argv[1], O_WRONLY);
  ERROR_CHECK(fd, -1, "open");

  ssize_t wret = write(fd, "hello wangshuai", strlen("hello wangshuai"));
  ERROR_CHECK(wret, -1, "write");
}
