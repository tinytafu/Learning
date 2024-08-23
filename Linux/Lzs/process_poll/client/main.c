#include "client.h"
#include <tytofu.h>

int main(int argc, char *argv[]) {
  //./client 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  // 建立连接
  int sockfd = establishConnection(argv[1], argv[2]);
  CHECK_MYSELF(sockfd, -1);
  // 调用epoll_create创建一个epoll实例
  int epfd = epoll_create(1);
  ERROR_CHECK(epfd, -1, "epoll_create");
  // 定义一个epoll_event对象
  struct epoll_event event;
  // 添加sockfd到监听集合
  int ret = addMonitor(epfd, sockfd, &event);
  CHECK_MYSELF(ret, -1);
  // 添加STDIN_FILENO到监听集合
  ret = addMonitor(epfd, STDIN_FILENO, &event);
  CHECK_MYSELF(ret, -1);
  // 定义一个保存就绪集合数据的数组和缓冲区
  char buf[4096] = {0};
  struct epoll_event readySet[2] = {0};
  // eventloop
  while (1) {
    bzero(readySet, sizeof(readySet));
    // 调用epoll_wait进行对事件的轮询
    int readyNum = epoll_wait(epfd, readySet, 2, -1);
    ERROR_CHECK(readyNum, -1, "epoll_wait");
    for (int i = 0; i < readyNum; i++) {
      if (readySet[i].data.fd == sockfd) {
        int ret = dealSockfd(sockfd, buf, sizeof(buf));
        CHECK_MYSELF(ret, -1);
      } else if (readySet[i].data.fd == STDIN_FILENO) {
        int ret = dealStdin(STDIN_FILENO, sockfd, buf, sizeof(buf));
        CHECK_MYSELF(ret, -1);
      }
    }
  }
  return EXIT_SUCCESS;
}
