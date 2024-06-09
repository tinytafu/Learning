// 打开文件
#include <tytofu.h>

int main(int argc, char *argv[]) {
  // 设置umask
  umask(0000);
  // tf file
  ARGS_CHECK(argc, 2);
  // 读写方式打开,如果文件不存在则创建,存在则清空
  int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0664);
  ERROR_CHECK(fd, -1, "open");
}
