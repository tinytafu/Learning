/*测试可执行程序所在路径在环境变量PATH下与不在的情况下的对比*/

#include <stdio.h>
#include <unistd.h>
/*测试命令行参数
 * argc:表示的是命令行参数的个数
 * argv:指针数组,存储的是各个参数的内容,以字符串的形式
 * 假如说我执行当前源代码编译链接后的可执行程序带上三个参数./myproc -1 -2 -3
 * 那么argc的值就是4 argv数组里的4个数据元素值就是"./myproc" "-1" "-2" "-3"*/
int main (int argc,char *argv[]) {

  for(int i = 0;i < argc;i++) {
    printf("argv[%d] is %s\n",i,argv[i]);
  }
  // while(1) {
  //   printf("hello world\n");
  //   sleep(1);
  // }
}
