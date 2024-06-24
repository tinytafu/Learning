#include <tytofu.h>

long global = 0;
// 创建自己的mutex
int mutex = 0;
void *routine(void *arg) {

  // 判断mutex是否为1,若为1则继续等待或者处理其他事情
  if (mutex == 1) {
  }
  // 如果不为1,则设置mutex为1,开始执行临界区代码
  // 以上操作是上锁
  mutex = 1;
  for (int i = 0; i < 10000; i++) {
    global++;
    //  read global;
    //  increment;
    //  write global
  }
  // 执行完毕之后,将mutex设置0
  mutex = 0;
  // 这是解锁
  return NULL;
}
int main() {
  pthread_t t1, t2;
  // 创建第一个线程
  if (pthread_create(&t1, NULL, routine, NULL) != 0)
    return 1;
  if (pthread_create(&t2, NULL, routine, NULL) != 0)
    return 1;
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("global is %ld\n", global);
  return EXIT_SUCCESS;
}
