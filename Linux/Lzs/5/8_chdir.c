// 更改calling process的工作路径
#include <stdio.h>
#include <tytofu.h>

int main() {
  // 获取进程id
  printf("my pid is %d\n", getpid());
  // 设置需要更改的路径
  const char *new_cwd = "/home/tinytofu/Development/C/";
  // 更改路径
  int ret = chdir(new_cwd);
  ERROR_CHECK(ret, -1, "chdir");
  // 获取新的路径信息
  char *pcwd = getcwd(NULL, 0);
  ERROR_CHECK(pcwd, NULL, "getwd");
  printf("pcwd is %s\n", pcwd);
  // 在新的工作路径下创建新的目录
  umask(0000);
  int ret_mk = mkdir("new_file", 0777);
  ERROR_CHECK(ret_mk, -1, "mkdir");
}
