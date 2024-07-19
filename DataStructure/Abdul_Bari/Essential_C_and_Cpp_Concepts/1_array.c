#include <stdio.h>

int main() {
  /*-------------------------------------*/
  int arr[5] = {10, 20, 30, 40, 50};
  printf("arr[%d] is %d\n", 0, arr[0]);
  printf("arr[%d] is %d\n", 1, arr[1]);
  printf("arr[%d] is %d\n", 2, arr[2]);
  printf("arr[%d] is %d\n", 3, arr[3]);
  printf("arr[%d] is %d\n", 4, arr[4]);
  // use for loop
  for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
    printf("arr[%d] is %d\n", i, arr[i]);
  }
  /*-------------------------------------*/
  int num[10] = {2};
  for (int i = 0; i < 10; i++)
    printf("num[%d] is %d\n", i, num[i]);
  /*-------------------------------------*/
  int n;
  scanf("%d", &n);
  int var[n];
  var[0] = 2;
  for (int i = 0; i < n; i++)
    printf("var[%d] is %d\n", i, var[i]);

  return 0;
}
