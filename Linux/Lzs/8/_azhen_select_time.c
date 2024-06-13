// aqing与azhen建立全双工通信,azhen先接收数据
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf 1.pipe 2.pipe
  ARGS_CHECK(argc, 3);
  // 打开1.pipe管道文件的写端,只让进程创建,若文件存在则报错
  int fdw = open(argv[1], O_WRONLY);
  // 记录open 1.pipe阻塞的时间
  // 检查是否打开成功
  ERROR_CHECK(fdw, -1, "open");
  // time_t pipe1_time = time(NULL);
  // 打开2.pipe管道文件的读端
  int fdr = open(argv[2], O_RDONLY);
  // 检查是否打开成功
  ERROR_CHECK(fdr, -1, "open");
  time_t pipe2_time = time(NULL);
  // printf("pipe1_time is %ld\n,pipe2_time is %ld", pipe1_time, pipe2_time);
  // 数据流通 -- 从stdin读取数据 -- 将数据从1.pipe的写端写入到文件对象中
  // -- 1.pipe的读端进行读取 反过来从2.pipe的读端进行读取数据发送到stdout中
  char buf[2048] = {0};
  // 创建监听集合
  fd_set rdset;
  // 定义设置超时时间的变量
  struct timeval timeout;
  while (1) {
    // 设置超时时间为1s,目的就是与time函数配合不会出现跳秒的情况,保证timeout的连续性
    timeout.tv_usec = 0;
    timeout.tv_sec = 1;
    // 初始化监听集合
    FD_ZERO(&rdset);
    // 将需要监听的文件对象添加到rdset -- 监听集合
    FD_SET(fdr, &rdset);
    FD_SET(STDIN_FILENO, &rdset);
    // 调用select,内核os会轮询检测监听的对象是否有数据传入,此时进程会阻塞
    int ret = select(fdr + 1, &rdset, NULL, NULL, &timeout);
    // 设置就绪时间 -- 无论是azhen输入数据还是aqiang输入数据都先以这个就绪为准
    time_t _total_time = time(NULL);
    // printf("_total_time is %ld\n wait for %ld s\n", _total_time,
    // _total_time - pipe2_time);
    if ((_total_time - pipe2_time) > 10) {
      printf("断开连接!\n");
      break;
    }
    // 判断select是否是因为超时就绪
    if (0 == ret) {
      // printf("timeout!\n");
      continue;
    }
    // select调用结束,代表os内核检测到至少某个文件对象条件就绪,判读是那个
    if (FD_ISSET(fdr, &rdset)) {
      // 若是因为aqiang发送数据导致select就绪,那么total_time记录的时间就是aqiang再次就绪的时间,
      // 将其值赋值给pipe2_time
      pipe2_time = _total_time;
      // 读取2.pipe管道文件的数据,将数据发送到stdout
      memset(buf, 0, sizeof(buf));
      ssize_t rret = read(fdr, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      if (0 == rret)
        break;
      printf("buf:%s", buf);
    }
    if (FD_ISSET(STDIN_FILENO, &rdset)) {
      // 读取stdin中的数据
      memset(buf, 0, sizeof(buf));
      ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      if (0 == rret)
        break;
      // 将读取到的数据发送到1.pipe
      ssize_t wret = write(fdw, buf, rret);
      ERROR_CHECK(wret, -1, "write");
    }
  }
  close(fdr);
  close(fdw);

  // char buf[2048] = {0};
  // 循环读取数据
  // while (1) {
  // 读取数据之前先清空buf
  // memset(buf, 0, sizeof(buf));
  // 1.aqiang先发送数据,那么azhen需要先从2.pipe的读端获取数据
  /* ssize_t read_fdr = read(fdr, buf, sizeof(buf));
  ERROR_CHECK(read_fdr, -1, "read"); */
  // 2.将读取的到数据发送到stdout
  /* ssize_t write_stdout = write(STDOUT_FILENO, buf, read_fdr);
  ERROR_CHECK(write_stdout, -1, "write");

  memset(buf, 0, sizeof(buf)); */
  // 3.azhen需要发送数据给aqiang,那么也是需要从stdin获取
  /* ssize_t read_stdin = read(STDIN_FILENO, buf, sizeof(buf));
  ERROR_CHECK(read_stdin, -1, "read"); */

  // 4.将读取到的数据发送到1.pipe的写端
  /* ssize_t write_fdw = write(fdw, buf, read_stdin);
  ERROR_CHECK(write_fdw, -1, "write"); */
  // }
  /* close(fdr);
  close(fdw); */
  // 由于是aqing先发送数据,因此为了避免阻塞,先从2.pipe读取数据
  /* char buf[4096];
  memset(buf, 0, sizeof(buf));
  ssize_t rret = read(fdr, buf, sizeof(buf));
  ERROR_CHECK(rret, -1, "read");
  ssize_t wret = write(STDOUT_FILENO, buf, rret);
  ERROR_CHECK(wret, -1, "write"); */

  // 从stdin读取数据
  /* memset(buf, 0, sizeof(buf));
  ssize_t rret1 = read(STDIN_FILENO, buf, sizeof(buf));
  ERROR_CHECK(rret1, -1, "read");
  ssize_t wret1 = write(fdw, buf, rret1);
  ERROR_CHECK(wret1, -1, "write");
  close(fdr);
  close(fdw); */
}
