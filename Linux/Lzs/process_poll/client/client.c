#include "client.h"
#include <strings.h>
#include <sys/socket.h>
#include <tytofu.h>
// 建立连接
int establishConnection(const char *ip, const char *port) {
  if (ip == NULL || port == NULL)
    return -1;
  // 打开一个socket文件对象
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置需要连接服务器的ip+port
  struct sockaddr_in serverAddr = {.sin_family = AF_INET,
                                   .sin_port = htons(atoi(port)),
                                   .sin_addr.s_addr = inet_addr(ip)};
  // 调用connect进行连接,发送第一次握手
  int ret_connect =
      connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  ERROR_CHECK(ret_connect, -1, "connect");
  // 返回文件对象的fd
  return sockfd;
}
// 添加对象到监听集合
int addMonitor(int epfd, int sockfd, struct epoll_event *event) {
  if (epfd < 0 || sockfd < 0 || event == NULL)
    return -1;
  event->data.fd = sockfd;
  event->events = EPOLLIN;
  int ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, event);
  return 0;
}
// 处理sockfd
int dealSockfd(int sockfd, char *buf, int buf_size) {
  if (sockfd < 0 || buf == NULL || buf_size == 0)
    return -1;
  bzero(buf, buf_size);
  int ret_recv = recv(sockfd, buf, buf_size, 0);
  ERROR_CHECK(ret_recv, -1, "RECV");
  printf("%s\n", buf);
  return 0;
}
// 处理stdin
int dealStdin(int stdinfd, int sockfd, char *buf, int buf_size) {
  if (stdinfd < 0 || sockfd < 0 || buf == NULL || buf_size == 0)
    return -1;
  bzero(buf, buf_size);
  int ret_read = read(STDIN_FILENO, buf, buf_size);
  ERROR_CHECK(ret_read, -1, "read");
  int ret_send = send(sockfd, buf, ret_read, 0);
  ERROR_CHECK(ret_send, -1, "send");
  return 0;
}
