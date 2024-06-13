// 打开两个管道
#include <tytofu.h>
int main(int argc, char **argv) {
  // 程序如何执行:./19_azhen 1.pipe 2.pipe
  ARGS_CHECK(argc, 3);
  // 打开管道文件1.pipe
  int fd1 = open(argv[1], O_WRONLY);
  ERROR_CHECK(fd1, -1, "open");
  int fd2 = open(argv[2], O_RDONLY);
  ERROR_CHECK(fd1, -1, "open");
}
