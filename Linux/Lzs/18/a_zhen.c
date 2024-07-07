#include <asm-generic/socket.h>
#include <stdio.h>
#include <strings.h>
#include <sys/select.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./a_zhen 192.168.0.103 2626
  ARGS_CHECK(argc, 3);
  /*建立tcp连接*/
  // 1.打开socket网络设备文件
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 2.绑定ip+port到socket
  struct sockaddr_in server_addr;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  server_addr.sin_family = AF_INET;
  int optval = 1;
  int ret_setsockopt =
      setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_bind, -1, "bind");
  // 监听
  int ret_listen = listen(sockfd, 50);
  ERROR_CHECK(ret_listen, -1, "listen");
  ERROR_CHECK(ret_setsockopt, -1, "setsockopt");
  /*断线重连接*/
  // 1.设置一个监听集合、就绪集合
  fd_set monitor_set;
  fd_set ready_set;
  // 2.初始化两个集合
  FD_ZERO(&monitor_set);
  FD_ZERO(&ready_set);
  // 3.首先将监听socket的fd添加到监听集合用于监听全连接队列中是否有先的连接到来
  FD_SET(sockfd, &monitor_set);
  int netfd = -1;
  char buf[4096];
  while (1) {
    // 将监听集合中的数据拷贝到就绪集合,用于select进行监听
    memcpy(&ready_set, &monitor_set, sizeof(monitor_set));
    // 调用select监听监听socket或者通信socket和stdin
    select(20, &ready_set, NULL, NULL, NULL);
    // 判断是否是监听socket就绪
    if (FD_ISSET(sockfd, &ready_set)) {
      // 调用accept将这个连接取出并构建一个通信socket文件对象
      netfd = accept(sockfd, NULL, NULL);
      ERROR_CHECK(netfd, -1, "accept");
      // 将monitor_set集合中的监听对象换成对通信socket文件对象
      // 和stdin用于与客户端的通信
      FD_CLR(sockfd, &monitor_set);
      FD_ZERO(&ready_set);
      // 将下一步要监听的文家对象的fd添加到monitor_set
      FD_SET(netfd, &monitor_set);
      FD_SET(STDIN_FILENO, &monitor_set);
      // 重新开始循环
      continue;
    }
    // 判断是否是通信socket设备就绪
    if (FD_ISSET(netfd, &ready_set)) {
      bzero(buf, sizeof(buf));
      // 读取通信文件中的读缓冲区数据
      ssize_t rret = recv(netfd, buf, sizeof(buf), 0);
      ERROR_CHECK(rret, -1, "recv");
      // 若客户端断开
      if (rret == 0) {
        // 更改monitor_set监听的对象
        FD_CLR(netfd, &monitor_set);
        FD_CLR(STDIN_FILENO, &monitor_set);
        // 清空就绪集合
        FD_ZERO(&ready_set);
        // 将监听socket文件对象添加到monitor_set
        FD_SET(sockfd, &monitor_set);
        // 关闭之前的通信socket文件对象
        close(netfd);
        // 将netfd设置为-1
        netfd = -1;
        // 继续循环
        continue;
      }
      // 若客户端没断开,将读取到的数据发送到stdout
      ssize_t wret = write(STDOUT_FILENO, buf, rret);
      ERROR_CHECK(wret, -1, "write");
    }
    if (FD_ISSET(STDIN_FILENO, &ready_set)) {
      bzero(buf, sizeof(buf));
      // 读取stdin中的数据
      ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      // 将读取到的数据发送到通信socket设备的写缓冲区
      ssize_t wret = send(netfd, buf, rret, 0);
      ERROR_CHECK(wret, -1, "send");
    }
  }
  return EXIT_SUCCESS;
}
