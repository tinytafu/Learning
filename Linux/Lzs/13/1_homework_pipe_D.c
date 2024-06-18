// 验证父子进程都关闭写端,读端读取的数据为0
#include <tytofu.h>

int main() {
  int fds[2];
  int ret = pipe(fds);
  if (fork()) {
    // 关闭写端
    close(fds[1]);
    // 关闭读端
    close(fds[0]);
    wait(NULL);
  } else {
    // 关闭写端
    close(fds[1]);
    char buf[1024] = {0};
    ssize_t rret = read(fds[0], buf, sizeof(buf));
    printf("rret is %ld\n", rret);
    exit(0);
  }
}
