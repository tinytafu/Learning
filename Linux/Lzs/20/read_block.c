#include <tytofu.h>

int main(int argc, char *argv[]) {
  //./read_block 1.pipe
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_RDONLY);
  ERROR_CHECK(fd, -1, "open");
  char buf[2] = {0};
  while (1) {
    bzero(buf, sizeof(buf));
    int ret_read = read(fd, buf, sizeof(buf));
    ERROR_CHECK(ret_read, -1, "read");
    printf("%s\n", buf);
    sleep(1);
  }
  return EXIT_SUCCESS;
}
