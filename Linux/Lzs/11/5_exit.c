// exit会刷新缓冲区,_exit不会刷新缓冲区 这是有妙用的
#include <tytofu.h>

void func() { // _exit(0);
  exit(0);
}
int main() {
  printf("hello");
  func();
  printf("can you see me?\n");
  return 0;
}
