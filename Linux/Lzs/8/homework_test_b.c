#include <sys/select.h>
#include <tytofu.h>

int main(int argc, char **argv) {
  // 程序如何执行:tf 3.pipe
  ARGS_CHECK(argc, 2);
  // 打开管道的写端
  int fdr = open(argv[1], O_RDONLY);
  ERROR_CHECK(fdr, -1, "open");

  // 先读取程序A发送的name,只读取100字节
  char name[100] = {0};
  ssize_t rret = read(fdr, name, sizeof(name));
  ERROR_CHECK(rret, -1, "read");
  // 再读取程序B发送的size,读取4字节二进制数据
  short file_size = 0;
  ssize_t rret1 = read(fdr, &file_size, sizeof(short));
  ERROR_CHECK(rret1, -1, "read");
  // 获取文件名还是需要判断的,到底使用的是绝对路径还是相对路径,还是只有一个文件名
  //  由于文件名发送过来的是绝对路径下的文件名,我只要文件名使用strtok
  //  char *position = strtok(name, "/");
  //  char *file_name = NULL;
  //  while (1) {
  //    position = strtok(NULL, "/");
  //    if (position == NULL)
  //      break;
  //    file_name = position;
  //  }
  //  while ((strtok(NULL, "/")) != NULL)
  //  ;
  printf("name is %s,file_size is %hd\n", name, file_size);

  // 拿到文件名和大小,在当前目录下创建一个目录dir保存这个文件
  char dir[1024] = "/home/tinytofu/Learning/Linux/Lzs/8/dir/";
  const char *pathname = strcat(dir, name);
  int ret = mkdir("dir", 0777);
  ERROR_CHECK(ret, -1, "mkdir");
  // 打开这个文件
  int fd = open(pathname, O_WRONLY | O_CREAT, 0666);
  ERROR_CHECK(fd, -1, "open");
  // 读取文件内容
  char buf[4096] = {0};
  fd_set rdset;
  while (1) {
    // 初始化监听集合
    FD_ZERO(&rdset);
    // 添加需要监听的文件描述符
    FD_SET(fdr, &rdset);
    // 调用select
    select(fdr + 1, &rdset, NULL, NULL, NULL);
    ssize_t rret = read(fdr, buf, sizeof(buf));
    ERROR_CHECK(rret, -1, "read");
    if (0 == rret)
      break;
    ssize_t wret = write(fd, buf, rret);
    ERROR_CHECK(wret, -1, "write");
  }
  close(fdr);
  close(fd);
}
