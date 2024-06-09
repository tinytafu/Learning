#include <tytofu.h>
int main(int argc, char **argv) {
  // 程序如何执行:tf file
  ARGS_CHECK(argc, 2);
  printf("you can see me!\n");
  // 关闭stdout对应的文件描述符1
  close(STDOUT_FILENO);
  // 打开文件 根据描述符分配规则,此时文件描述符1就是我们打开的文件对应的文件对象
  int fd = open(argv[1], O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  // printf是默认绑定文件描述符1的,那么此时输出的内容就到了被打开的文件了
  printf("you can't see me !\n");
  close(fd);
}
