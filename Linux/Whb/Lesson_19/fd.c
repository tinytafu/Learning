#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("stdin:%d", stdin->_fileno);
  printf("stdout:%d", stdout->_fileno);
  printf("stderr:%d", stderr->_fileno);
}
