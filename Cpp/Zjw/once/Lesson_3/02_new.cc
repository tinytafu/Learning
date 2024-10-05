/*动态内存分配*/

#include <iostream>
#include <cstdlib>
using namespace std;
int main () {
  int *pm = (int*)malloc(sizeof(int));
  //查看一下malloc申请的堆内存空间存储的初始值是多少
  std::cout << "*pm is " << *pm << std::endl;
  free(pm);
  pm = NULL;
  free(pm);
  
  int *pn = new int;//返回指向int类型的指针类型的地址值
  //查看一下初始值
  cout << "*pn is " << *pn << endl;
  delete pn;
  pn = NULL;
  delete pn;
  int *parr = new int[4];
  cout << "*parr is " << *parr << endl;
  delete[] parr;
  char *ptr_ch = new char[5]{'w','a','n','g','\0'};
  for(int i = 0;ptr_ch[i];i++) {
    cout << "ptr_ch[" << i << "]: " << ptr_ch[i] << endl;
  }
  delete [] ptr_ch;
}
