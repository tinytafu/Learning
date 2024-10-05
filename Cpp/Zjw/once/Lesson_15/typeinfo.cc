// 运行时类型信息 RTTI
#include <iostream>
#include <typeinfo>

int main() {
  int m = 10;
  const std::type_info &type = typeid(m);
  const char *name = type.name();
  std::cout << name << std::endl;
}
