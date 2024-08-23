#include <iostream>
#include <unistd.h>

int main() {
  char buf[1024] = {0};
  int ret = read(STDIN_FILENO, buf, sizeof(buf));
  std::cout << ret << std::endl;
  printf(",%s,", buf);
}
