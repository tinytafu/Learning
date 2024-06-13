// select
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:_aqiang_select 1.pipe 2.pipe
  ARGS_CHECK(argc, 3);
  // 打开1.pipe的读端
  int fdr = open(argv[1], O_RDONLY);
  ERROR_CHECK(fdr, -1, "open");
  // 打开2.pipe的写端
  int fdw = open(argv[2], O_WRONLY);
  ERROR_CHECK(fdw, -1, "open");

  // 创建一个fd_set,用于监听所需资源的阻塞设备
  fd_set rdset;
  char buf[2048] = {0};
  while (1) {
    // 初始化rdset
    FD_ZERO(&rdset);
    // 添加需要监听的设备描述符,分别是1.pipe的读端和stdin
    FD_SET(fdr, &rdset);
    FD_SET(STDIN_FILENO, &rdset);
    // 调用select,此时os在执行select的时候会进行轮询检测,若无资源就绪,进程一直阻塞
    int ret = select(fdw + 1, &rdset, NULL, NULL, NULL);
    // 如果select检测到阻塞设备有一个条件就绪,将rdset设置为就绪集合,需要判断这个就绪集合中哪个设备
    // 就绪执行对应的操作
    if (FD_ISSET(STDIN_FILENO, &rdset)) {
      // 读取stdin的数据,将其写入到2.pipe中
      memset(buf, 0, sizeof(buf));
      ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      if (0 == rret)
        break;
      ssize_t wret = write(fdw, buf, rret);
      ERROR_CHECK(wret, -1, "write");
    }
    if (FD_ISSET(fdr, &rdset)) {
      // 读取1.pipe的数据,将其输出到stdout
      memset(buf, 0, sizeof(buf));
      ssize_t rret = read(fdr, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      if (0 == rret)
        break;
      printf("buf:%s", buf);
    }
    // 由于调用select,os会进行轮询检测,检测成功之后会将rdset这个监听集合更改为就绪集合.那么再次监听呢?
    // 还是要将rdset重置,因此是需要将FD_ZERO放入循环的
  }
  close(fdr);
  close(fdw);
}
