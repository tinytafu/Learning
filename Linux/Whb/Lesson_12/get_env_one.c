//获取环境变量的第一种方式

#include <stdio.h>

int main(int argc,char *argv[],char *env[]) {
  for(int i = 0;env[i];i++) 
    printf("env[%d] is %s\n",i,env[i]);
}
