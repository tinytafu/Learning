// 守护进程：脱离启动环境,不受其他设置影响,无论在那个地方启动,保持再同一路径下启动

#include <tytofu.h>
void daemon_s() {
  // 新建会话
  if (fork())
    exit(0);
  setsid();
  // 关闭设备
  for (int i = 0; i < 64; i++) {
    close(i);
  }
  // 修改环境属性
  umask(0000);
  chdir("/");
}

int main() {
  daemon_s();
  for (int i = 0; i < 20; i++) {
    syslog(LOG_INFO, "i am daemon,i = %d\n", i);
    sleep(2);
  }
  return 0;
}
