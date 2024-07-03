#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <tytofu.h>
int main(int argc, char *argv[]) {
  //./select_serevr 192.168.0.103 2626
  // 调用socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置ip+port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 使用bind绑定ip + port
  int res_bind =
      bind(sockfd, (struct sockaddr *)&(server_addr), sizeof(server_addr));
  // 监听
  int res_lis = listen(sockfd, 50);
  ERROR_CHECK(res_lis, -1, "listen");
  // 接收消息和发送消息
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  int netfd = accept(sockfd, (struct sockaddr *)&addr, &addr_len);
  ERROR_CHECK(netfd, -1, "accept");
  // 输出连接的客户端的ip_port
  // printf("clint: ip is %s,port is %d\n", inet_ntoa(addr.sin_addr),
  // ntohs(addr.sin_port));

  // 设置监听集合
  fd_set rdset;
  while (1) {
    // 初始化监听集合
    FD_ZERO(&rdset);
    // 添加监听对象到监听集合
    FD_SET(netfd, &rdset);
    FD_SET(STDIN_FILENO, &rdset);
    // 调用select
    select(netfd + 1, &rdset, NULL, NULL, 0);
    // 判断就绪集合中的对象是谁
    if (FD_ISSET(netfd, &rdset)) {
      char buf[4096] = {0};
      // 读取文件对象中读缓冲区的数据
      ssize_t rret = recv(netfd, buf, sizeof(buf), 0);
      ERROR_CHECK(rret, -1, "rret");
      // 输出数据到控制台
      ssize_t wret = write(STDOUT_FILENO, buf, rret);
      ERROR_CHECK(wret, -1, "write");
    }
    if (FD_ISSET(STDIN_FILENO, &rdset)) {
      // 读取标准输入的数据
      char buf[4096] = {0};
      ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      // 将读取到的数据发送到socket文件对象中的写缓冲区中
      ssize_t wret = send(netfd, buf, rret, 0);
      ERROR_CHECK(wret, -1, "write");
    }
  }
}
