#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>
#include <tytofu.h>

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
  // 向服务器发送数据
  ssize_t wret = send(sockfd, "hello", strlen("hello"), 0);
  ERROR_CHECK(wret, -1, "send");
  // 接收服务器发送的数据
  char buf[4096] = {0};
  ssize_t rret = recv(sockfd, buf, sizeof(buf), 0);
  printf("%s\n", buf);
  ERROR_CHECK(rret, -1, "recv");
  return EXIT_SUCCESS;
}
