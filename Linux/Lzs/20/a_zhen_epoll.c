#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./a_zhen_epoll 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  // 打开socket文件对象
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置绑定的ip和port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 忽略TIME_WAIT

  // 利用bind绑定
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof server_addr);
  ERROR_CHECK(ret_bind, -1, "bind");

  // 侦听连接
  int ret_listen = listen(sockfd, 100);
  ERROR_CHECK(ret_listen, -1, "listen");
  struct sockaddr_in clint_addr;
  socklen_t length = sizeof(clint_addr);
  // 从全连接队列中拿出一个连接创建一个与客户端通信的文件对象
  int netfd = accept(sockfd, (struct sockaddr *)&clint_addr, &length);
  printf("clint_addr is %s,port is %d\n", inet_ntoa(clint_addr.sin_addr),
         ntohs(clint_addr.sin_port));
  ERROR_CHECK(netfd, -1, "accept");

  // 创建一个epoll instance
  int epfd = epoll_create(526);
  ERROR_CHECK(epfd, -1, "epoll");
  struct epoll_event event;
  // 设置监听netfd事件属性
  event.events = EPOLLIN;
  event.data.fd = netfd;
  // 将监听对象添加到epoll示例中的interest list
  int ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  // 设置监听STDIN_FILENO事件属性
  event.events = EPOLLIN;
  event.data.fd = STDIN_FILENO;
  ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
  char buf[4096] = {0};

  // 定义一个struct epoll_event类型的数组用于保存
  // interest中就绪的事件
  struct epoll_event events[1024];
  while (1) {
    int ret_epoll_wait = epoll_wait(epfd, events, 2, -1);
    ERROR_CHECK(ret_epoll_wait, -1, "epoll_wait");
    // 对就绪集合中事件进行遍历
    for (int i = 0; i < ret_epoll_wait; i++) {
      if (events[i].data.fd == STDIN_FILENO) {
        bzero(buf, sizeof(buf));
        // 读取stdin中的数据
        int ret_read = read(STDIN_FILENO, buf, sizeof buf);
        ERROR_CHECK(ret_read, -1, "read");
        // 将读取到的数据发送到服务端
        int ret_send = send(netfd, buf, ret_read, 0);
        ERROR_CHECK(ret_send, -1, "send");
      } else if (events[i].data.fd == netfd) {
        bzero(buf, sizeof(buf));
        int ret_recv = recv(netfd, buf, sizeof(buf), 0);
        ERROR_CHECK(ret_recv, -1, "recv");
        int ret_write = write(STDOUT_FILENO, buf, ret_recv);
        ERROR_CHECK(ret_write, -1, "write");
      }
    }
  }
  return EXIT_SUCCESS;
}
