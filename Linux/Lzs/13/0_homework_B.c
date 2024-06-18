// 遍历当前目录,输出所有目录项的名称
#include <dirent.h>
#include <tytofu.h>

int main(int argc, char *argv[]) {
  ARGS_CHECK(argc, 2);
  // 打开目录
  DIR *dp = opendir(argv[1]);
  ERROR_CHECK(dp, NULL, "opendir");
  struct dirent *act;
  while ((act = readdir(dp)) != NULL) {
    printf("%s\n", act->d_name);
  }
  return EXIT_SUCCESS;
}
