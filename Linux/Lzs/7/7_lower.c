// 将文件中的大写字符转换为小写 -- 采用read/write顺序读写的方式
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf file
  ARGS_CHECK(argc, 2);
  // 打开文件
  int fd = open(argv[1], O_RDWR);
  // 检测文件是否打开失败
  ERROR_CHECK(fd, -1, "open");

  // 使用read每次只读取一个字节
  char ch;
  while (1) {
    ssize_t rret = read(fd, &ch, 1);
    ERROR_CHECK(rret, -1, "read");
    if (0 == rret)
      break;
    if (ch >= 'A' && ch <= 'Z') {
      ch += 32;
      // read读取完一个字符会自动向后移动一位,write将在移动的那一位进行写字符,不仅不会覆盖当前读写
      // 位置的字符,还覆盖后面一位
      // 使用lseek调整写的位置
      off_t lret = lseek(fd, -1, SEEK_CUR);
      ssize_t wret = write(fd, &ch, rret);
      ERROR_CHECK(wret, -1, "write");
    }
  }
  close(fd);
}
