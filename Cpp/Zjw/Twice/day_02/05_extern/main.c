#include <stdio.h>
extern int sum(int a,int b);
extern int sub(int a,int b);
int main (){
  int const var1 = 20;
  int const var2 = 30;
  printf("var1 + var2 = %d\n",sum(var1,var2));
  printf("va1 - var2 = %d\n",sub(var1, var2));
  return 0;
}
