//获取环境变量的第二种方式

#include <stdio.h>
#include <unistd.h>


extern char **environ;//libc中定义的全局变量,在此处只是声明,链接阶段与libc中的定义进行链接
int main () {
  for(int i= 0;environ[i];i++)
    printf("environ[%d] is %s\n",i,environ[i]);
}
