#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (2 != argc) {
    printf("Usage:./a.out filename");
    exit(-1);
  }
  FILE *fp = fopen(argv[1], "r");
  if (NULL == fp) {
    perror("fopen");
    exit(-1);
  }

  char buf[64] = {'\0'};
  while (fgets(buf, sizeof(buf), fp)) {
    fputs(buf, stdout);
  }
  fclose(fp);
}
