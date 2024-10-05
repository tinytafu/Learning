//名字空间嵌套与名字空间别名
#include <iostream>

namespace ns {
  int value = 100;
  namespace ns1{
    int value = 200;
    namespace ns2 {
      int value = 300;
      namespace ns3{
        int value = 400;
      }
    }
  }
}

int main () {
  //访问ns3中的value
  std::cout << "ns::ns1::ns2::ns3::value is " << ns::ns1::ns2::ns3::value << std::endl;
  //使用名字空间别名
  namespace ns_three = ns::ns1::ns2::ns3;
  std::cout << "ns_three::value is " << ns_three::value << std::endl; 
}
