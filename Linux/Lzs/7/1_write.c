// 读取file文件中的数据
#include <tytofu.h>

int main(int argc, char *argv[]) {
  // 设置进程权限掩码
  umask(0000);
  // 程序如何执行:tf file
  ARGS_CHECK(argc, 2);
  // 打开一个文件
  int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  // 检查是否打开失败
  ERROR_CHECK(fd, -1, "open");
  // 往文件对象中写数据
  ssize_t sret = write(fd, "hello tofu", strlen("hello tofu"));
  // 检查是否写入失败
  ERROR_CHECK(sret, -1, "write");
  // 查看write的返回值,返回的是写入的数据字节数
  printf("sret is %ld\n", sret);
  close(fd);
}
