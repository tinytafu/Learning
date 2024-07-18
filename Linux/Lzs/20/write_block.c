#include <stdio.h>
#include <tytofu.h>

int main(int argc, char *argv[]) {
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_WRONLY);
  ERROR_CHECK(fd, -1, "open");
  ssize_t ret_write = write(fd, "howareyou", strlen("howareyou"));
  ERROR_CHECK(ret_write, -1, "write");
  sleep(20);
  return EXIT_SUCCESS;
}
