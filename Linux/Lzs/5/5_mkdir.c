// 创建目录
#include <tytofu.h>

int main(int argc, char *argv[]) {
  umask(0000);
  // 如何执行 tf dir
  ARGS_CHECK(argc, 2);
  // 创建目录
  int ret = mkdir(argv[1], 0777);
  // 检查是否创建失败
  ERROR_CHECK(ret, -1, "mkdir");
}
