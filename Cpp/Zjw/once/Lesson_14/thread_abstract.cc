// 模拟一个"通用"的线程类,将线程类设置为抽象类
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::flush;
class thread {
public:
  // 定义一个成员函数创建线程
  void start(/*thread *this*/) {
    pthread_create(&tid, NULL, routine, (void *)this);
  }
  // 等待线程退出
  void join() { pthread_join(tid, NULL); }
  // 可以将一个普通成员函数设置为一个线程入口函数吗
  // 是不可以的,因为线程入口函数只有一个void*类型的参数,但是
  // 普通成员函数中还有一个编译器自己添加的参数 thread* this.
  // 但是在类中是有一个方法的,将其设置为static函数即可
  // 在静态函数中调用虚函数
private:
  virtual void func() = 0;
  static void *routine(void *arg) {
    thread *thisp = (thread *)arg;
    thisp->func();
    pthread_exit(NULL);
  }
  pthread_t tid;
};
class man : public thread {
public:
  void func() {
    for (;;) {
      usleep(100 * 500);
      cout << "-" << flush;
    }
  }
};

int main() {
  man m1;
  m1.start();
  m1.join();
}
