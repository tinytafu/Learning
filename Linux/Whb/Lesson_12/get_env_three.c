//获取环境变量第三种方式

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main () {
  //利用环境变量获取当前用户名
  const char *user = getenv("USER");
  printf("user is %s\n",user);
  //可以利用环境变量获取的变量名设置权限
  if(strcasecmp(user, "tinytofu") == 0)
    printf("do!\n");
  else {
    printf("权限不足!\n");
    return 0;
  }
}
