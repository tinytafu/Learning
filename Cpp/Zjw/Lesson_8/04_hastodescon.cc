// 自定义析构函数

#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using std::cout;
using std::endl;

class human {
public:
  human() : m_name(new char), m_fd(open("log.txt", O_RDWR | O_CREAT, 0644)) {
    /*const char* m_name = new char;*/
    /*int m_fd = open("log.txt",O_RDWR | O_CREAT,0644)*/
  }
  ~human() {
    delete m_name; /*释放m_name指向的堆内存资源*/
    close(m_fd);   /*释放m_fd打开的文件资源*/
    cout << "释放动态资源完毕" << endl;
    /*释放m_name、m_fd所占的内存空间*/
  }

private:
  char *m_name;
  int m_fd;
};

int main() { human h1; }
