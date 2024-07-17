#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./a_qiang_select 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  // 打开socket文件对象
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  // 设置需要连接的ip + port
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 发送连接 第一次握手
  int ret_connect =
      connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_connect, -1, "connect");

  fd_set monitor_set;
  fd_set ready_set;
  FD_ZERO(&monitor_set);
  FD_ZERO(&ready_set);
  // 添加监听对象到监听集合
  FD_SET(sockfd, &monitor_set);
  FD_SET(STDIN_FILENO, &monitor_set);
  char buf[4096] = {0};
  while (1) {
    memcpy(&ready_set, &monitor_set, sizeof(fd_set));
    int ret_select = select(sockfd + 1, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &ready_set)) {
      bzero(buf, sizeof(buf));
      ssize_t ret_recv = recv(sockfd, buf, sizeof(buf), 0);
      ERROR_CHECK(ret_recv, -1, "recv");
      if (ret_recv == 0) {
        printf("server disconnect!\n");
        break;
      }
      ssize_t ret_write = write(STDOUT_FILENO, buf, ret_recv);
      ERROR_CHECK(ret_write, -1, "write");
    }
    if (FD_ISSET(STDIN_FILENO, &ready_set)) {
      bzero(buf, sizeof(buf));
      ssize_t ret_read = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(ret_read, -1, "read");
      if (ret_read == 0) {
        printf("client disconnect\n");
        break;
      }
      ssize_t ret_send = send(sockfd, buf, sizeof(buf), 0);
      ERROR_CHECK(ret_send, -1, "send");
    }
  }
  return EXIT_SUCCESS;
}
