#include <tytofu.h>

int main(int argc, char *argv[]) {
  // 判断argc是否为2
  // if (2 != argc) {
  //   fprintf(stderr, "args error!\n");
  //   exit(-1);
  // }
  ARGS_CHECK(argc, 2);
  // 以读写打开文件
  FILE *fp = fopen(argv[1], "r+");
  if (NULL == fp) {
    perror("fopen");
    exit(-1);
  }
}
