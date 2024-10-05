#include <iostream>


int main () {
  //除了void类型之外,其他的基本类型都可以进行隐式转换
  int a = 10;
  short sh = 200;
  long lo = 300;
  long long ll = 3000;

  char b = 'a';

  float c = 22.1f;
  double d = 22.22;
  long double ld = 22.333;
  bool e = true;
  a = sh = lo = ll = b = c = d = ld = e;
  e = ld = d = c = b = ll = lo = sh = a;

  /* 任何其他基本类型的指针都可以隐式转换到void* */
  void* pv = &a;
  pv =  &sh;
  pv = &lo;
  pv = &ll;

  pv = &b;

  pv = &c;
  pv = &d;
  pv = &ld;

  pv = &e;

  /*void* 到 任何其他类型的指针都必须强转*/
  pv = &a;
  // int* pa = (int*)pv;
  int* pa = static_cast<int*>(pv);
  pv = &sh;
  // short* psh = (short*)pv;
  short* psh = static_cast<short*>(pv);
  pv = &lo;
  // long* plo = (long*)pv;
  long* plo = static_cast<long*>(pv);
  pv = &ll;
  // long long* pll = (long long*)pv;
  long long* pll = static_cast<long long*>(pv);
  pv = &b;
  // char* pb = (char*)pv;
  char* pb = static_cast<char*>(pv);
  pv = &c;
  // float* pc = (float*)pv;
  float* pc = static_cast<float*>(pv);
  pv = &d;
  // double* pd = (double*)pv;
  double* pd = static_cast<double*>(pv);
  pv = &ld;
  // long double* pld = (long double*)pv;
  long double* pld = static_cast<long double*>(pv);
  pv = &e;
  // bool* pe = (bool*)pv;
  bool* pe = static_cast<bool*>(pv);
  
  /*任何类型的非常指针 到 同类型的常指针都可以隐式转换*/
  const int* cpa = pa;
  const short* cpsh = psh;
  const long* cplo = plo;
  const long long* cpll = pll;
  const char* cpb = pb;
  const float* cpc = pc;
  const double* cpd = pd;
  const long double* cpld = pld;
  const bool* cpe = pe;

  /*任何类型的常指针 到 同类型的非常指针都必须强转*/
  // pa = (int*)cpa;
  pa = const_cast<int*>(cpa);
  // psh = (short*)cpsh;
  psh = const_cast<short*>(cpsh);
  // plo = (long*)cplo;
  plo = const_cast<long*>(cplo);
  // pll = (long long*)cpll;
  pll = const_cast<long long*>(cpll);
  // pb = (char*)cpb;
  pb = const_cast<char*>(cpb);
  // pc = (float*)cpc;
  pc = const_cast<float*>(cpc);
  // pd = (double*)cpd;
  pd = const_cast<double*>(cpd);
  // pld = (long double*)cpld;
  pld = const_cast<long double*>(cpld);
  // pe = (bool*)cpe;
  pe = const_cast<bool*>(cpe);

  /*除了void*以外,其他类型的指针都必须强转*/

  // pa = (int*)psh;
  pa = reinterpret_cast<int*>(psh);
  /*任意类型的指针和整数之间的转换*/
  pa = reinterpret_cast<int*>(100000);

}
