// dup
#include <tytofu.h>
int main(int argc, char **argv) {
  // 程序如何执行:tf file
  ARGS_CHECK(argc, 2);
  // 打开文件
  int oldfd = open(argv[1], O_RDWR);
  ERROR_CHECK(oldfd, -1, "open");
  // 使用dup返回一个新的描述符与oldfd指向同一个文件对象,共享偏移量
  int newfd = dup(oldfd);
  ERROR_CHECK(newfd, -1, "dup");

  // 写入数据
  ssize_t sret = write(oldfd, "hello", strlen("hello"));
  ssize_t sret1 = write(newfd, "world", strlen("world"));
  close(oldfd);
  close(newfd);
}
