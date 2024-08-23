#include <stdio.h>

int main() {
  const int a = 20;
  /*int arr[a] = {};*/
  int *p = (int *)&a;
  *p = 10;
  printf("%d %d %d\n", a, *p, *(&a));
}
