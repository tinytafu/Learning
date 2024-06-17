#include <tytofu.h>

int main(int argc, char **argv) {
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_RDWR);
  ERROR_CHECK(fd, -1, "open");

  // fork之后,父子维护的文件描述符表中各有一个文件描述符指向同一个打开文件描述,共享偏移量
  switch (fork()) {
  case -1: {
    perror("fork");
    break;
  }
  case 0: {
    write(fd, "hello", 5);
    _exit(0);
  }
  default: {
    // 让父进程阻塞等待子进程执行完毕,否则父子同时对一个文件写入数据,会出现竞争条件,结果不会按照
    // 自己预期的那样,父子进程需要一定的同步
    wait(NULL);
    write(fd, "world", strlen("world"));
    exit(0);
  }
  }
}
