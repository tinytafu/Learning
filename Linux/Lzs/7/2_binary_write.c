// 写入内存数据到文本
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf file_binary
  ARGS_CHECK(argc, 2);
  // 打开文件
  int fd = open(argv[1], O_WRONLY);
  // 检查是否打开失败
  ERROR_CHECK(fd, -1, "open");

  // 定义一个4字节的栈内存数据
  int i = 1000000;
  // 写入数据到文件
  ssize_t ret = write(fd, &i, sizeof(int));
  ERROR_CHECK(ret, -1, "write");
  // 查看写入数字大小
  printf("ret is %ld\n", ret);
  close(fd);
}
