// 奇怪的代码
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  const char *str1 = "hello puts\n";
  const char *str2 = "hello write\n";
  // C库函数
  printf("hello printf\n");
  fprintf(stdout, "hello fprintf\n");
  fputs(str1, stdout);
  // 系统调用
  write(1, str2, strlen(str2));
  // 执行完上述代码,执行fork
  fork();
}
