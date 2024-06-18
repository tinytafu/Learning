// 验证读端关闭,再次往匿名管道写入数据的时候,会收到SIGPIPE信号,导致程序异常退出
#include <tytofu.h>
void handler(int signum) { printf("我收到%d号信号了\n", signum); }
int main(int argc, char *argv[]) {
  // 注册信号
  signal(SIGPIPE, handler);
  int fds[2];
  int ret = pipe(fds);
  if (fork()) {
    // 父进程关闭读端,此时读端是父子进程都引用的,关闭一个只是减少了文件对象的引用次数,若想将此文件
    // 对象直接关闭,子进程也是需要关闭的
    close(fds[0]);
    // 等待子进程关闭读端和写端
    sleep(5);
    printf("sleep over\n");
    write(fds[1], "hello", 5);
    printf("can you see me?\n");
    wait(NULL);
  } else {
    // 关闭读端、写端
    close(fds[1]);
    close(fds[0]);
    while (1) {
      sleep(1);
    }
  }
  return EXIT_SUCCESS;
}
