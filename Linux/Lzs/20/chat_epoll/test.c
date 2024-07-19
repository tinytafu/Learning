#include <stdio.h>
#include <string.h>

int main() {
  char *name = "wangshuai";
  printf("%p\n", name);
  // 当一个字符指针指向一个字符串常量的时候,是不可以作为strcat中的dest
  // 因为字符串常量在.rodata段中
  // dest只能存储堆或者段区域内的地址
  char *dest = strcat(name, ": ");
}
