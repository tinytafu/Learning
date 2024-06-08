#include <tytofu.h>

int main(int argc, char *argv[]) {
  ARGS_CHECK(argc, 2);
  // 打开文件
  FILE *fp = fopen(argv[1], "r+");
  // 判断是否打开错误
  ERROR_CHECK(fp, NULL, "fopen");
  // 存储读取的数据
  char buf[1024] = {0};
  int ret = fread(buf, 1, sizeof(buf), fp);
  ERROR_CHECK(ret, -1, "fread");
  fprintf(stdout, "buf is %s\n", buf);
}
