#include <cstdio>
#include <iostream>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <vector>
using namespace std;

typedef void (*hand)();

vector<hand> hands;
void fun1() {
  cout << "i am fun1!" << endl;
}
void fun2() {
  cout << "i am fun2!" << endl;
}
void fun3() {
  cout << "i am fun3!" << endl; 
}
void load() {
  hands.push_back(fun1);
  hands.push_back(fun2);
  hands.push_back(fun3);
}



int main () {
  pid_t pid = fork();
  if( 0 == pid) {
    while(1) {
      cout << "I am child process! I'm not exit! my pid = "  << getpid() << endl;
      sleep(1);
    }
  }
  else if(pid > 0) {
    int status = 0;
    //decla funtion array
    // hand hands[3] = {fun1,fun2,fun3};
    while(1) {
      sleep(1);
      //not block wait
      pid_t ret = waitpid(pid, &status, WNOHANG);
      if (ret > 0) {
        cout << "wait success!exit code of child process is " << WEXITSTATUS(status) << endl <<  "exit signal of child process is " << (status&0x7F) << endl;
        break;
      }else if(0 == ret) {
        cout << "wait success!father process need to do other things because child process not exit!" << endl;
        // for(int i = 0;i < sizeof(hands) / sizeof(hands[0]);i++){
        //   hands[i]();
        // }
        if(hands.empty()) load();
        for(auto f : hands) {
          f();
        }
      }else {
        cout << "wait failed!" << endl;
        break;
      }
    }
  }
}


// int main () {
//   //创建一个子进程
//   pid_t id = fork();
//
//
//   if(0 == id) {
//     while(1) {
//       cout << "我是子进程 pid = " << id << endl;
//       char* ptr = NULL;
//       *ptr = 'a';
//     }
//   }else {
//     //存储子进程的退出信息
//     int status = 0;
//     //等待子进程退出
//     pid_t ret = waitpid(id, &status, 0);
//     if (WIFEXITED(status)){
//       cout << "等待成功!" << endl;
//       cout << "退出码为" << WEXITSTATUS(status) << endl; 
//     } else {
//       cout << "非正常退出!" << endl;
//     }
//     if (ret > 0){
//       cout << "进程的退出码为:" << ((status>>8)&0xFF) << "\n" << "进程的退出信号为:" << (status&0x7F) << endl;
//     }
//   }
// }
