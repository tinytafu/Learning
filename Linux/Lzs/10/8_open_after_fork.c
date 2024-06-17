// fork之后父子进程在打开同一个文件,不会共享偏移量,但是inode是指向同一个文件的
// 也就是说后写入的的数据是会覆盖先写入的,其实这里应该也是有竞争条件产生的trace
// condition
#include <tytofu.h>

int main(int argc, char **argv) {
  ARGS_CHECK(argc, 2);

  switch (fork()) {
  case -1:
    perror("fork");
  case 0: {
    int fd = open(argv[1], O_RDWR);
    write(fd, "hello", strlen("hello"));
    _exit(0);
  }
  default: {
    // wait(NULL);
    int fd = open(argv[1], O_RDWR);
    write(fd, "world", strlen("world"));
    char buf[10] = {0};
    // 目前pos指向了文件末尾,无论是读还是写都是末尾的下一个字节
    // 调整偏移量
    lseek(fd, 0, SEEK_SET);
    ssize_t rret = read(fd, buf, sizeof(buf));
    printf("rret is %ld\n", rret);
    exit(0);
  }
  }
}
