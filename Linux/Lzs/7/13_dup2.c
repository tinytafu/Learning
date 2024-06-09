// dup2
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf file
  ARGS_CHECK(argc, 2);
  // 打开文件
  int fd = open(argv[1], O_RDWR | O_TRUNC);
  // 检查文件打开是否失败
  ERROR_CHECK(fd, -1, "open");
  printf("我过来了!\n");
  int fd_backup = 12;
  int fd_back = dup2(STDOUT_FILENO, fd_backup);
  ERROR_CHECK(fd_back, -1, "dup2");
  int fd1 = dup2(fd, STDOUT_FILENO);
  ERROR_CHECK(fd1, -1, "dup2");
  printf("我过去了!\n");
  int fd2 = dup2(fd_backup, STDOUT_FILENO);
  printf("我又过来了!\n");
  close(fd);
  close(fd1);
  close(fd2);
}
