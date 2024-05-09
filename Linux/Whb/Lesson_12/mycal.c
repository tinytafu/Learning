/*写一个简易的命令行版本的计算器理解命令行参数*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*usage:./mycal [-a | -s | -d | -s] one_data two_data*/
int main(int argc, char *argv[]) {
  int x = atoi(argv[2]);
  int y = atoi(argv[3]);
  if (argc != 4) {
    printf("usage:./mycal [-a | -s | -m | -d] one_data two_data\n");
    return 0;
  }
  if (strcmp(argv[1], "-a") == 0)
    printf("%d + %d = %d\n", x, y, x + y);
  else if (strcmp(argv[1], "-s") == 0)
    printf("%d - %d = %d\n", x, y, x - y);
  else if (strcmp(argv[1], "-m") == 0)
    printf("%d * %d = %d\n", x, y, x * y);
  else if((strcmp(argv[1], "-d") == 0) && y != 0) 
    printf("%d / %d = %d\n",x,y,x / y);
  else 
   printf("usage:./mycal [-a | -s | -m | -d] one_data two_data\n");
}
