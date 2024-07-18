// 读取磁盘文件时不会阻塞,当文件中没有数据的时候不会阻塞
#include <tytofu.h>

int main(int argc, char *argv[]) {
  //./read_nonblock file1
  int fd = open(argv[1], O_RDONLY);
  ERROR_CHECK(fd, -1, "open");
  char buf[2] = {0};
  while (1) {
    bzero(buf, sizeof(buf));
    int ret_read = read(fd, buf, sizeof(buf));
    sleep(1);
    printf("%s\n", buf);
  }
  return EXIT_SUCCESS;
}
