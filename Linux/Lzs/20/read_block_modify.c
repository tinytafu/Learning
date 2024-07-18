#include <tytofu.h>
// 更改管道文件的属性,使其读取数据的时候,若没有数据则不阻塞
int modify_fd(int fd) {
  int fd_flags = fcntl(fd, F_GETFL);
  fd_flags = fd_flags | O_NONBLOCK;
  int ret = fcntl(fd, F_SETFL, fd_flags);
  ERROR_CHECK(ret, -1, "fcntl");
  return 0;
}
int main(int argc, char *argv[]) {
  //./read_block 1.pipe
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_RDONLY);
  ERROR_CHECK(fd, -1, "open");
  modify_fd(fd);
  char buf[2] = {0};
  while (1) {
    bzero(buf, sizeof(buf));
    ssize_t ret_read = read(fd, buf, sizeof(buf));
    printf("ret_read = %ld,buf = %s\n", ret_read, buf);
    sleep(1);
  }
  return EXIT_SUCCESS;
}
