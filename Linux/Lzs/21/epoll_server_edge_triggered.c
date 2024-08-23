#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./epoll_server 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  // 打开一个网络文件对象
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "sockfd");
  // 设置需要绑定的ip+port
  struct sockaddr_in server_addr = {.sin_family = AF_INET,
                                    .sin_port = htons(atoi(argv[2])),
                                    .sin_addr.s_addr = inet_addr(argv[1])};
  // 地址重用
  int reuse = 1;
  int ret_setsockopt =
      setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  ERROR_CHECK(ret_setsockopt, -1, "setsockopt");
  // 将ip+port绑定到sockfd对应的网络文件对象
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_bind, -1, "bind");
  // 对sockfd对应的网络文件对象进行监听
  // 此时将改变sockfd对应的网络文件对象中的数据结构,内部将会有
  // 两个队列,一个半连接队列,一个是全连接队列
  int ret_listen = listen(sockfd, 1024);
  ERROR_CHECK(ret_listen, -1, "listen");
  // 当全连接队列中有数据到来时,调用accept对全连接队列中读取数据,若无数据则阻塞
  // 定义一个保存客户端信息的对象
  struct sockaddr_in client_addr;
  socklen_t length = sizeof(client_addr);
  int netfd = accept(sockfd, (struct sockaddr *)&client_addr, &length);
  ERROR_CHECK(netfd, -1, "accept");
  // 将客户端的信息打印到stdout
  printf("clint ip:%s\nclient port:%hu\n", inet_ntoa(client_addr.sin_addr),
         ntohs(client_addr.sin_port));
  // 创建一个epoll实例
  int epfd = epoll_create(1);
  ERROR_CHECK(epfd, -1, "epoll_create");
  // 将监听的对象添加到监听集合
  struct epoll_event event;
  event.data.fd = netfd;
  // 将通信文件对象的事件就绪加上边缘触发
  event.events = EPOLLIN | EPOLLET;
  int ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  event.events = EPOLLIN;
  event.data.fd = STDIN_FILENO;
  ret_epoll_ctl = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
  ERROR_CHECK(ret_epoll_ctl, -1, "epoll_ctl");
  // 定义一个保存就绪集合的数据结构
  struct epoll_event readySet[2];
  // 网络文件对象缓冲区 每次读取2个字节
  char buf_net[2] = {0};
  // stdin文件对象缓冲区
  char buf_stdin[10] = {0};
  // eventloop
  while (1) {
    // 初始化用户态就绪集合
    bzero(readySet, sizeof(readySet));
    // 调用epoll_wait
    int readyNum = epoll_wait(epfd, readySet, 2, -1);
    ERROR_CHECK(readyNum, -1, "epoll_wait");
    // 遍历就绪集合
    for (int i = 0; i < readyNum; i++) {
      if (readySet[i].data.fd == netfd) {
        printf("epoll_wait is ready!\n");
        // 清空缓冲区
        bzero(buf_net, sizeof(buf_net));
        // 读取通信文件对象内读缓冲区中的数据
        while (1) { // 循环加非阻塞
          int ret_recv = recv(netfd, buf_net, sizeof(buf_net), MSG_DONTWAIT);
          if (ret_recv == -1)
            break;
          // 将读取到的数据发送到stdout
          printf("%s\n", buf_net);
        }
      } else if (readySet[i].data.fd == STDIN_FILENO) {
        // 清空缓冲区
        bzero(buf_stdin, sizeof(buf_stdin));
        // 读取stdin中的数据
        int ret_read = read(STDIN_FILENO, buf_stdin, sizeof(buf_stdin));
        ERROR_CHECK(ret_read, -1, "read");
        // 将读取到的数据发送到通信文件对象中的发送缓冲区
        int ret_send = send(netfd, buf_stdin, ret_read, 0);
        ERROR_CHECK(ret_send, -1, "send");
      }
    }
  }
  return EXIT_SUCCESS;
}
