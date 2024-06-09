// 查看语言级别中的FILE*指针stdout stdin stderr中的对应的文件对象描述符是什么
#include <tytofu.h>

int main() {
  // 程序如何执行:tf
  // C语言级别的FILE* stderr是无缓冲的
  fprintf(stdout, "stdout->_fileno:%d", fileno(stdout));
  fprintf(stderr, "stderr->_fileno:%d", fileno(stderr));
  fprintf(stdout, "stdin->_fileno:%d", fileno(stdin));
  sleep(10);
}
