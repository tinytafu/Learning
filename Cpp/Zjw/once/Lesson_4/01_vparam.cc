#include <iostream>

void Swap(int* ptr_a,int* ptr_b){
  int x = *ptr_a;
  *ptr_a = *ptr_b;
  *ptr_b = x;
}
void Swap(int& ref_a,int& ref_b){
  int x = ref_a;
  ref_a = ref_b;
  ref_b = x;
}
void Swap(const int& cref_a,const int& cref_b) {
  //cref_a = 10;//error
  std::cout << "cref_a: " << cref_a << "cref_b: " << cref_b << std::endl;
}

int main () {
  int a = 10;
  int b = 20;
  //Swap(&a,&b);
  Swap(10,20);
}
