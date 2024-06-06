#include <cstdio>
#include <iostream>

int main() {
  // stdout
  printf("hello printf 1\n");
  fprintf(stdout, "hello fprintf 1\n");
  fputs("hello fputs 1\n", stdout);

  // stderr
  fprintf(stderr, "hello fprintf 2\n");
  fputs("hello fputs 2\n", stderr);
  perror("hello perror 2");

  // cout
  std::cout << "hello cout 1" << std::endl;
  // cerr
  std::cerr << "hello cerr 2" << std::endl;
}
