// 创造一个自定义的cp命令程序,一次性读取到的数据越大,trap的次数越少
#include <tytofu.h>

int main(int argc, char **argv) {
  // 如何执行程序:tf file1 file2
  ARGS_CHECK(argc, 3);
  // 打开file1 file2
  int fd1 = open(argv[1], O_RDONLY);
  int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

  /*一次读取*/
  // 存储从file1读取到的数据
  // char buf[10] = {0};
  // ssize_t sret = read(fd1, buf, sizeof(buf));
  // ERROR_CHECK(sret, -1, "read");
  // 将读取到的数据写入到file2
  // ssize_t sret1 = write(fd2, buf, sret);
  // 检查是否写入成功
  // ERROR_CHECK(sret1, -1, "write");
  /*一次读取*/

  /*循环读取*/
  char buf[5] = {
      0}; // char数组是为了更方便的控制内存大小,毕竟char是占一个内存单元的
  // read读取到文件末尾会返回0,以read返回值不等于0作为循环继续的条件
  while (1) {
    // 养成一个好习惯,每次读取到一块内存区域,先将这块区域清空
    memset(buf, 0, sizeof(buf));
    ssize_t sret = read(fd1, buf, sizeof(buf));
    ERROR_CHECK(sret, -1, "read");
    // 判断是否读到文件末尾
    if (0 == sret)
      break;
    // 使用read读取到的字节数作为write的写入字节数
    ssize_t sret1 = write(fd2, buf, sret);
    ERROR_CHECK(sret1, -1, "write");
  }
  close(fd1);
  close(fd2);
}
