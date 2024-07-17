#include "inline.hpp"
#include <iostream>
void func(int a, int b = 20);
void func(int a = 10, int b);
int main() { return 0; }

void func(int a, int b) { std::cout << a + b << std::endl; }
