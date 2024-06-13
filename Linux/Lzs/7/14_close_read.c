// 管道读端
#include <tytofu.h>
int main(int argc, char **argv) {
  // 程序如何执行:1.pipe
  ARGS_CHECK(argc, 2);

  // 打开管道文件读端
  int fd = open(argv[1], O_RDONLY);
  ERROR_CHECK(fd, -1, "open");
  printf("read side is opened!\n");
  /*关闭读端*/
  sleep(5);
  close(fd);
  // char buf[1024] = {0};
  // ssize_t sret = read(fd, buf, sizeof(buf));
  // ERROR_CHECK(sret, -1, "read");
  // printf("sret is %ld\n", sret);
}
