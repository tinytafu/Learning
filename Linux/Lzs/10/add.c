#include <stdio.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char **argv) {
  ARGS_CHECK(argc, 3);
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  printf("%d\n", a + b);
}
