#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  int fd = open("log.txt", O_RDONLY);
  if (fd < 0) {
    perror("open:");
    exit(-1);
  }
}
