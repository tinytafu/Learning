#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {

  // 更改进程所在路径
  // chdir("/home/tinytofu/文档");
  // 打开文件
  FILE *fp = fopen("log.txt", "a");
  if (NULL == fp) {
    perror("fopen");
    exit(-1);
  }

  // printf("mypid = %d\n", getpid());
  // while (1) {
  //   sleep(1);
  // }

  // 写入的数据
  const char *msg = "hello wangshuai ";
  int cnt = 1;
  while (cnt < 5) {
    fprintf(fp, "%s: %d\n", msg, cnt++);
  }
  fclose(fp);
}
