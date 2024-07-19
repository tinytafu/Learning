#include <stdio.h>
struct rectangle {
  char x;
  int length;
  int breadth;
};
int main() {
  struct rectangle r1 = {.length = 10, .breadth = 15, .x = 'a'};
  r1.x = 'b';
  printf("sizeof(r1) is %zu\n", sizeof(r1));
  printf("r1.x = %c\n", r1.x);
  return 0;
}
