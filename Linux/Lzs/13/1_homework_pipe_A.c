#include <tytofu.h>
// 验证读阻塞:父进程先休眠5秒开始写入数据,子进程读取的时候是无数据的,会阻塞
int main(int argc, char *argv[]) {
  int fds[2];
  int ret = pipe(fds); // fds[0]:read,fds[1]:write
  ERROR_CHECK(ret, -1, "pipe");
  if (fork()) {
    // 父进程关掉读端fds[0]
    close(fds[0]);
    // 先睡上5秒,先让子进程在无数据的时候读取,看看是否阻塞,保持同步
    sleep(5);
    printf("sleep over\n");
    write(fds[1], "hello", 5);
    exit(0);
  } else {
    // 子进程关掉自己的写端
    close(fds[1]);
    // 读取匿名管道中的数据
    char buf[4096] = {0};
    ssize_t rret = read(fds[0], buf, sizeof(buf));
    printf("rret = %ld,buf = %s\n", rret, buf);
    _exit(0);
  }
  return EXIT_SUCCESS;
}
