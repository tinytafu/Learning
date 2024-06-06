#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void my_perror(const char *str) {
  fprintf(stderr, "%s: %s\n", str, strerror(errno));
}

int main() {
  int fd = open("log.txt", O_RDONLY);
  if (fd < 0) {
    perror("open");
    my_perror("my open");
    exit(-1);
  }
}
