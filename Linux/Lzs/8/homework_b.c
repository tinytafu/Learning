// 编写程序A和B,A向B发送文件的名称、大小、内容,程序B创建目录并保存文件
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf 3.pipe
  ARGS_CHECK(argc, 2);
  // 打开管道文件的读端
  int fdr = open(argv[1], O_RDONLY);
  ERROR_CHECK(fdr, -1, "open");
}
