// 加载到一个目录到内存和关闭一个目录流
#include <tytofu.h>

int main(int argc, char *argv[]) {
  // 如何执行?在进程当前工作路径加载目录dir tf dir
  ARGS_CHECK(argc, 2);
  // 加载dir目录到内存
  DIR *pdir = opendir(argv[1]);
  // 检查是否打开错误
  ERROR_CHECK(pdir, NULL, "opendir");

  // 关闭一个DIR*
  closedir(pdir);
}
