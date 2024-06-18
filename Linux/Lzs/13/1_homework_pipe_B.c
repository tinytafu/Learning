// 验证写阻塞：父子进程分别不停的写入和读取,但是父进程写入的数据是子进程读取数据的两倍
#include <tytofu.h>

int main(int argc, char *argv[]) {
  int fds[2];
  int ret = pipe(fds);
  ERROR_CHECK(ret, -1, "pipe");
  if (fork()) {
    close(fds[0]);
    int cnt = 0;
    while (1) {
      char buf[4096] = {0};
      write(fds[1], buf, sizeof(buf));
      printf("parent ret = %d\n", cnt++);
      sleep(1);
    }
  } else {
    close(fds[1]);
    int cnt = 0;
    while (1) {
      char buf[2048] = {0};
      ssize_t rret = read(fds[0], buf, sizeof(buf));
      printf("child cnt = %d\n", cnt++);
      sleep(1);
    }
  }
  return EXIT_SUCCESS;
}
