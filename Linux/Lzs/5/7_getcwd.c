// 获取进程的当前工作路径 -- 绝对路径
#include <tytofu.h>

int main(int argc, char *argv[]) {

  // 定义一个buf存储当前进程所在的绝对路径的字符串数据
  // char buf[1024] = {0};
  // char *buf = malloc(1024);
  // if (NULL == buf) {
  //   printf("malloc error!\n");
  //   exit(-1);
  // }
  // 调用getcwd
  // char *pcwd = getcwd(buf, sizeof(buf));
  // char *pcwd = getcwd(buf, 1024);
  // char *pcwd = getcwd(buf, 10);
  char *pcwd = getcwd(NULL, 0);
  ERROR_CHECK(pcwd, NULL, "getcwd");
  printf("pcwd is %s\n", pcwd);
  free(pcwd);
}
