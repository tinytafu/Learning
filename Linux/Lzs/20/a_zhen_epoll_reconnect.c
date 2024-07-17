// 断线重连
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <tytofu.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //./a_zhen_epoll_reconnect 192.169.199.148 2626
  ARGS_CHECK(argc, 3);
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockfd, -1, "socket");
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  int ret_bind =
      bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  ERROR_CHECK(ret_bind, -1, "bind");
  int ret_listen = listen(sockfd, 100);

  int epfd = epoll_create(526);
  ERROR_CHECK(epfd, -1, "epoll_create");
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = sockfd;
  epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
  struct epoll_event events[1024];
  char buf[4096] = {0};
  int netfd = -1;
  while (1) {
    int ret_epoll_wait = epoll_wait(epfd, events, 1024, -1);
    ERROR_CHECK(ret_epoll_wait, -1, "epoll_wait");
    for (int i = 0; i < ret_epoll_wait; i++) {
      if (events[i].data.fd == sockfd) {
        netfd = accept(sockfd, NULL, NULL);
        ERROR_CHECK(netfd, -1, "accept");
        epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
        event.events = EPOLLIN;
        event.data.fd = netfd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &event);
        event.data.fd = STDIN_FILENO;
        epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
        printf("client is connected!\n");
      } else if (events[i].data.fd == netfd && netfd != -1) {
        bzero(buf, sizeof(buf));
        int ret_recv = recv(netfd, buf, sizeof(buf), 0);
        if (ret_recv == 0) {
          printf("client is disconnected!\n");
          epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, NULL);
          epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, NULL);
          event.events = EPOLLIN;
          event.data.fd = sockfd;
          epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
          close(netfd);
          netfd = -1;
          break;
        }
        ERROR_CHECK(ret_recv, -1, "recv");
        int ret_write = write(STDOUT_FILENO, buf, ret_recv);
        ERROR_CHECK(ret_write, -1, "write");
      } else if (events[i].data.fd == STDIN_FILENO) {
        bzero(buf, sizeof(buf));
        int ret_read = read(STDIN_FILENO, buf, sizeof(buf));
        if (ret_read == 0) {
          exit(-1);
        }
        ERROR_CHECK(ret_read, -1, "read");
        int ret_send = send(netfd, buf, ret_read, 0);
        ERROR_CHECK(ret_send, -1, "ret_send");
      }
    }
  }
  return EXIT_SUCCESS;
}
