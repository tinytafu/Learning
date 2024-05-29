#include <stdio.h>
#define A 0x1 /*0001*/
#define B 0x2 /*0010*/
#define C 0x4 /*0100*/
#define D 0x8 /*1000*/

void show_flags(int flags) {
  switch (flags) {
  case A: {
    printf("A\n");
    break;
  }
  case A | B: {
    printf("A|B\n");
    break;
  }
  case A | B | C: {
    printf("A|B|C\n");
    break;
  }
  case B | C: {
    printf("B|C\n");
    break;
  }
  default: {
    printf("no set other output");
  }
  }
}
int main() {
  show_flags(A | B);
  show_flags(A);
  show_flags(A | B | C);
}
