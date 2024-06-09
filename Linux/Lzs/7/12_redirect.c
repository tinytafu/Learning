// dup + close(STDOUT_FILENO)
#include <tytofu.h>
int main(int argc, char **argv) {
  // 程序如何执行:tf file
  ARGS_CHECK(argc, 2);
  // 打开文件
  int oldfd = open(argv[1], O_RDWR | O_TRUNC);
  ERROR_CHECK(oldfd, -1, "open");
  printf("you can see me!\n");
  close(STDOUT_FILENO);
  // 使用dup返回一个新的描述符1与oldfd指向同一个文件对象,共享偏移量
  int newfd = dup(oldfd);
  ERROR_CHECK(newfd, -1, "dup");
  printf("you can't see me!\n");
  close(oldfd);
  close(newfd);
}
