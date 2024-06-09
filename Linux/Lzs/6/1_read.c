// 读取文件
#include <fcntl.h>
#include <tytofu.h>

int main(int argc, char *argv[]) {
  umask(0000);
  // tf file
  ARGS_CHECK(argc, 2);
  // 读写方式打开文件,存在则清空,不存在则创建
  int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
  // 读写文件
  // 建立一块内存存储读取到的数据
  char buf[1024] = {0};
  // sret是读取到的实际字节数 sizeof(buf) -
  // 1是读取的最大上限,可能比其小,也可能为0
  ssize_t sret = read(fd, buf, sizeof(buf) - 1);
  ERROR_CHECK(sret, -1, "read");
  // 覆盖从文件读取的换行 注意读取数据大小的上限与实际读取到的数据大小是不一样的
  buf[sret - 1] = '\0';
  printf("buf is %s\n", buf);
}
