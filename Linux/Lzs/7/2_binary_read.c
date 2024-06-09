// 读取二进制文件 -- 必须是知道约定的 不然读取的字节不对,完整的数据就获取不到
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf fine_binary
  ARGS_CHECK(argc, 2);
  // 打开文件
  int fd = open(argv[1], O_RDONLY);
  // 检查是否打开失败
  ERROR_CHECK(fd, -1, "open");
  // 定义一个内存空间保存读取到的数据
  int i;
  ssize_t sret = read(fd, &i, sizeof(int));
  // 检查是否读取失败
  ERROR_CHECK(sret, -1, "read");
  // 输出读取到的数据
  printf("i is %d\n", i);
  close(fd);
}
