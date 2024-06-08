// 修改文件权限
#include <tytofu.h>

int main(int argc, char **argv) {
  // tf file1 ->更改file1的权限
  ARGS_CHECK(argc, 2);
  int ret = chmod(argv[1], 0664); // 八进制数据 开头为0
  ERROR_CHECK(ret, -1, "chmod");
}
