#include "student.h"
#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;
void routine() {
  cout << "thread one" << endl;
}

int main (){
  thread t1(routine);
  if(t1.joinable())
    t1.join();
  cout << "test make" << endl;
  student s1;
  return 0;
}
