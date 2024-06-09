// 写入字符序列到文本文件
#include <tytofu.h>
int main(int argc, char *argv[]) {
  // 程序如何执行:tf file2
  ARGS_CHECK(argc, 2);
  // 打开一个文件
  int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
  // 检查是否打开失败
  ERROR_CHECK(fd, -1, "open");

  // 将一个1000000的字符序列写入到文本文件
  char *buf = "1000000";
  ssize_t sret = write(fd, buf, strlen(buf));
  // 检查是否写入失败
  ERROR_CHECK(sret, -1, "write");
  // 还可使用字符数组的形式将文本数据读取到字符数组中
  char buf1[1024] = {0};
  off_t tret = lseek(fd, 0, SEEK_SET);
  // off_t tret = lseek(fd, -2, SEEK_CUR);
  ERROR_CHECK(tret, -1, "tret");
  ssize_t rret = read(fd, buf1, sizeof(buf1));
  ERROR_CHECK(rret, -1, "read");
  printf("rret is %ld\n", rret);
  close(fd);
}
