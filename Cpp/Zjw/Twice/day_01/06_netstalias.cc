//名字空间嵌套和别名
#include <iostream>
using std::cout;
using std::endl;

namespace ns1 {
  int g_value = 10;
  namespace ns2 {
    int g_value = 20;
    namespace ns3 {
      int g_value = 30;
      namespace ns4 {
        int g_value = 40;
      }
    }
  }
}

int main () {
  
  cout << "ns1::ns2::ns3::ns4::g_value: " << ns1::ns2::ns3::ns4::g_value << endl;
  namespace ns_four = ns1::ns2::ns3::ns4;
  cout << "ns_four::g_value: " << ns_four::g_value << endl;
  return 0;
}
