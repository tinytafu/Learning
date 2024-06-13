#include <sys/select.h>
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf 3.pipe
  ARGS_CHECK(argc, 3);
  // 打开管道的写端
  int fdw = open(argv[1], O_WRONLY);
  ERROR_CHECK(fdw, -1, "open");

  // 获取文件元数据
  // 文件大小
  short file_size = 0;
  // const char *path = "/home/tinytofu/Learning/Linux/Lzs/8/homework_test_a.c";
  struct stat file_stat;
  int ret = stat(argv[2], &file_stat);
  ERROR_CHECK(ret, -1, "stat");
  // 判断文件类型
  if (S_ISREG(file_stat.st_mode))
    file_size = file_stat.st_size;
  printf("file name is %s,size is %hd\n", argv[2], file_size);

  // 目前的3.pipe是可写的,对于写入是不阻塞的
  // 定义程序A和B之间,先发送文件名,且前100个字节是文件名
  char name[100] = {0};
  strncpy(name, argv[2], strlen(argv[2]));
  // 就写入100个字节
  ssize_t wret = write(fdw, name, sizeof(name));
  ERROR_CHECK(wret, -1, "write");
  // 再发送文件大小,以short类型发送
  ssize_t wret1 = write(fdw, &file_size, sizeof(short));

  // 发送文件内容,若文件内容过大,则可能发生写入阻塞,因此是需要监听管道W端是否可写
  /*打开此文件,读取此文件内容*/
  char buf[4096] = {0};
  int fd = open(argv[2], O_RDONLY);
  ERROR_CHECK(fd, -1, "open");
  fd_set wrset;
  while (1) {
    // 重置监听集合
    FD_ZERO(&wrset);
    // 将需要监听的文件描述符添加到监听集合
    FD_SET(fdw, &wrset);
    select(fdw + 1, NULL, &wrset, NULL, NULL);
    // 监听集合中只有一个监听的对象,那么当select就绪时,进程结束阻塞,只能是这一个对象所需的条件就绪
    ssize_t rret = read(fd, buf, sizeof(buf));
    ERROR_CHECK(rret, -1, "read");
    if (0 == rret)
      break;
    ssize_t wret = write(fdw, buf, rret);
    ERROR_CHECK(wret, -1, "write");
  }
  close(fdw);
  close(fd);
}
