// 文件流FILE与文件对象之间的关系
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行：tf file
  ARGS_CHECK(argc, 2);
  // 使用fopen打开一个文件
  FILE *fp = fopen(argv[1], "r+"); // 读写方式打开
  ERROR_CHECK(fp, NULL, "fopen");

  // fp指向的对象中包含一个指向文件对象的描述符号,我们可以使用fileno系统调用获取
  ssize_t w_ret = write(fileno(fp), "wangshuai", strlen("wangshuai"));
  ERROR_CHECK(w_ret, -1, "write");

  // 关闭文件
  fclose(fp);
}
