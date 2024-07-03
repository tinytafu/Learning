#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./clinet 192.168.0.103 2626
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置需要连接的ip和port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 调用connect进行连接
  int res_con =
      connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(res_con, -1, "connect");

  // 创建监听集合
  fd_set rdset;
  while (1) {
    // 初始化监听集合
    FD_ZERO(&rdset);
    // 将监听对象添加到监听集合
    FD_SET(sockfd, &rdset);
    FD_SET(STDIN_FILENO, &rdset);
    // 调用select
    select(sockfd + 1, &rdset, NULL, NULL, 0);
    if (FD_ISSET(sockfd, &rdset)) {
      // 读取socket文件对象中读缓冲区的数据
      char buf[4096] = {0};
      ssize_t rret = recv(sockfd, buf, sizeof(buf), 0);
      ERROR_CHECK(rret, -1, "recv");
      // 将读取到的数据写入到标准输出
      ssize_t wret = write(STDOUT_FILENO, buf, rret);
      ERROR_CHECK(wret, -1, "write");
    }
    if (FD_ISSET(STDIN_FILENO, &rdset)) {
      // 读取标准输入中的数据
      char buf[4096] = {0};
      ssize_t rret = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(rret, -1, "read");
      // 将读取到的数据写入到socket文件对象中的写缓冲区
      ssize_t wret = send(sockfd, buf, rret, 0);
      ERROR_CHECK(wret, -1, "send");
    }
  }
}
