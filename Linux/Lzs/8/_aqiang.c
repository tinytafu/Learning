// aqing与azhen建立全双工通信,aqing先发送数据
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf 1.pipe 2.pipe
  ARGS_CHECK(argc, 3);
  // 打开1.pipe管道文件的读端,只让进程创建,若文件存在则报错
  int fdr = open(argv[1], O_RDONLY);
  // 检查是否打开成功
  ERROR_CHECK(fdr, -1, "open");
  // 打开2.pipe管道文件的写端,只让进程创建,若文件存在则报错
  int fdw = open(argv[2], O_WRONLY);
  // 检查是否打开成功
  ERROR_CHECK(fdw, -1, "open");

  // 数据流通:  从stdin读取数据 -- 将数据从2.pipe的写端写入到文件对象中
  // -- 2.pipe的读端进行读取 反过来从1.pipe的读端读取对方的数据发送到stdout中
  char buf[4096] = {0};
  // 循环进行读取数据,发送数据
  while (1) {
    // 要从1.pipe和stdin读取数据到buf,养成良好规范读取之前,先都设置为0
    // 1.aqiang先发送数据,从stdin读取数据
    memset(buf, 0, sizeof(buf));
    ssize_t read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
    ERROR_CHECK(read_stdin, -1, "read");
    // 2.将读取的数据发送到2.pipe
    ssize_t write_fdw = write(fdw, buf, read_stdin);
    ERROR_CHECK(write_fdw, -1, "write");

    // 3.aqiang发送完数据,需要read读取1.pipe中azhen发送的数据
    memset(buf, 0, sizeof(buf));
    ssize_t read_fdr = read(fdr, buf, sizeof(buf));
    ERROR_CHECK(read_fdr, -1, "read");
    // 4.将读取到的数据发送到stdout
    ssize_t write_stdout = write(STDOUT_FILENO, buf, read_fdr);
    ERROR_CHECK(write_stdout, -1, "write");
  }
  close(fdr);
  close(fdw);

  /*一次读取数据*/
  // 1.从stdin读取数据
  // char buf[4096];
  // 每次读取之前清空buf
  /* memset(buf, 0, sizeof(buf));
  ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
  ERROR_CHECK(rret, -1, "read"); */
  // 2.将读取到的数据写入到2.pipe
  /* ssize_t wret = write(fdw, buf, rret);
  ERROR_CHECK(wret, -1, "write"); */

  // 3.从1.pipe读端读取数据
  /* memset(buf, 0, sizeof(buf));
  ssize_t rret1 = read(fdr, buf, sizeof(buf));
  ERROR_CHECK(rret1, -1, "read");
  ssize_t wret1 = write(STDOUT_FILENO, buf, rret1);
  ERROR_CHECK(wret1, -1, "write");
  close(fdr);
  close(fdw); */
}
