// 删除目录
#include <tytofu.h>

int main(int argc, char *argv[]) {
  // 如何执行:tf dir
  ARGS_CHECK(argc, 2);
  // 删除目录
  int ret = rmdir(argv[1]);
  ERROR_CHECK(ret, -1, "rmdir");
}
