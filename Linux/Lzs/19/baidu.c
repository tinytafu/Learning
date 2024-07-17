#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <tytofu.h>

int main() {
  // HTTP协议的请求
  const char query[] = "GET / HTTP/1.0\r\n"
                       "Host: www.baidu.com\r\n"
                       "\r\n";
  const char hostname[] = "www.baidu.com";
  struct hostent *entry = gethostbyname(hostname);
  if (NULL == entry) {
    herror("gethostbyname");
    return -1;
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");

  struct sockaddr_in serveraddr;
  serveraddr.sin_port = htons(80);
  serveraddr.sin_family = AF_INET;
  memcpy(&serveraddr.sin_addr, entry->h_addr_list[0],
         sizeof(serveraddr.sin_addr));

  int ret_con =
      connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  ERROR_CHECK(ret_con, -1, "connect");
  // 向百度服务器发送请求消息
  send(sockfd, query, sizeof(query), 0);
  char buf[4096] = {0};
  while (1) {
    bzero(buf, sizeof(buf));
    ssize_t ret = recv(sockfd, buf, sizeof(buf), 0);
    if (ret == 0) {
      break;
    }
    printf("ret is %ld\nbuf is %s\n", ret, buf);
  }
}
