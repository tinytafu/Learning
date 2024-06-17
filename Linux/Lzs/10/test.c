#include <stdio.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char **argv) {
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  char buf[10];
  ssize_t rret = read(fd, buf, sizeof buf);
  write(1, buf, rret);
}
