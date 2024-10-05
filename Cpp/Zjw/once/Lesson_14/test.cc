#include <iostream>

int main() {

  char **pphead = new char *[3]{"wangshuai", "huamengjun", "wangmi"};
  std::cout << (void *)pphead << std::endl;
  std::cout << (void *)(pphead + 1) << std::endl;
}
