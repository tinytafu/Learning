#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./chat_client 192.168.199.148 2626
  ARGS_CHECK(argc, 3);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  int ret_connect =
      connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_connect, -1, "connect");

  fd_set ready_set, monitor_set;
  FD_ZERO(&ready_set);
  FD_ZERO(&monitor_set);
  FD_SET(STDIN_FILENO, &monitor_set);
  FD_SET(sockfd, &monitor_set);
  char buf[4096] = {0};
  while (1) {
    memcpy(&ready_set, &monitor_set, sizeof(fd_set));
    select(sockfd + 1, &ready_set, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &ready_set)) {
      bzero(buf, sizeof(buf));
      int ret_recv = recv(sockfd, buf, sizeof(buf), 0);
      if (ret_recv == 0) {
        printf("I am disconnect!\n");
        break;
      }
      ERROR_CHECK(ret_recv, -1, "recv");
      int ret_write = write(STDOUT_FILENO, buf, ret_recv);
      ERROR_CHECK(ret_write, -1, "write");
    }
    if (FD_ISSET(STDIN_FILENO, &ready_set)) {
      bzero(buf, sizeof(buf));
      int ret_read = read(STDIN_FILENO, buf, sizeof(buf));
      ERROR_CHECK(ret_read, -1, "read");
      int ret_send = send(sockfd, buf, ret_read, 0);
      ERROR_CHECK(ret_send, -1, "send");
    }
  }
  return EXIT_SUCCESS;
}
