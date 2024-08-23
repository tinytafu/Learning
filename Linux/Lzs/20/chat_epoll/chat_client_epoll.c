#include <sys/socket.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./chat_client_epoll 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  // 打开socket文件对象
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置服务器的ip+port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 调用connect开启连接,发送第一次握手
  int ret_connect =
      connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_connect, -1, "connect");
  // 调用epoll_create创建一个epoll实例
  int epfd = epoll_create(526);
  ERROR_CHECK(epfd, -1, "epoll_create");
  // 设置监听对象的属性,并添加到epoll实例中的监听集合
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = STDIN_FILENO;
  int ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  event.events = EPOLLIN;
  event.data.fd = sockfd;
  ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  // 定义保存数据的缓冲区
  char buf[4096] = {0};
  // 定义用户态的就绪集合
  struct epoll_event ready_set[1024];
  while (1) {
    // 调用epoll_wait开启轮询
    int fd_number = epoll_wait(epfd, ready_set, 1024, -1);
    ERROR_CHECK(fd_number, -1, "epoll_wait");
    for (int i = 0; i < fd_number; i++) {
      if (ready_set[i].data.fd == STDIN_FILENO) {
        bzero(buf, sizeof(buf));
        int ret_read = read(STDIN_FILENO, buf, sizeof(buf));
        ERROR_CHECK(ret_read, -1, "read");
        // 将读取到的数据发送到通信对象中的写缓冲区
        int ret_send = send(sockfd, buf, ret_read, 0);
        ERROR_CHECK(ret_send, -1, "send");
      } else if (ready_set[i].data.fd == sockfd) {
        bzero(buf, sizeof(buf));
        // 定义一个变量保存读取到的端口号
        uint16_t port;
        int ret_recv = recv(sockfd, &port, sizeof(port), 0);
        if (ret_recv == 0) {
          printf("hehe\n");
          exit(-1);
        }
        ERROR_CHECK(ret_recv, -1, "recv");
        // 定义一个变量保存读取到的ip地址
        struct in_addr ip;
        ret_recv = recv(sockfd, &ip, sizeof(ip), 0);
        ERROR_CHECK(ret_recv, -1, "recv");
        // 读取发送的数据
        ret_recv = recv(sockfd, buf, sizeof(buf), 0);
        ERROR_CHECK(ret_recv, -1, "recv");
        printf("%s:%hu-> %s\n", inet_ntoa(ip), ntohs(port), buf);
      }
    }
  }
  return EXIT_SUCCESS;
}
