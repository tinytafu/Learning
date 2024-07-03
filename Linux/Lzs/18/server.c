#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>
#include <tytofu.h>
int main(int argc, char *argv[]) {
  //./server 192.168.0.103 2626
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
  printf("clint: ip is %s,port is %d\n", inet_ntoa(addr.sin_addr),
         ntohs(addr.sin_port));
  // 接收客户端的数据
  char buf[4096] = {0};
  ssize_t rret = recv(netfd, buf, sizeof(buf), 0);
  printf("%s\n", buf);
  ERROR_CHECK(rret, -1, "recv");
  // 收到消息之后向客户端发送数据
  ssize_t wret = send(netfd, "how are you?", strlen("how are you?"), 0);
  ERROR_CHECK(wret, -1, "send");
}
