// 子类类型的指针或者引用可以隐式转换为基类类型的指针或者引用

#include <iostream>
using std::cout;
using std::endl;
using std::string;
#pragma pack(1)
class human {
public:
  int m_age;
};
class student : public human {
public:
  long m_id;
};

int main() {
  student s1;
  s1.m_age = 10;
  s1.m_id = 20;
  cout << "s1的所占内存的大小为" << sizeof(s1) << endl;
  // 指向子类类型的指针隐式转换为指向基类类型的指针
  human *p_h = &s1;
  // 对子类类型的引用可以隐式转换为对基类类型的引用
  human &ref_h = s1;

  // 这种强转是允许的,且访问也是正确的
  student *stu = static_cast<student *>(p_h);
  student &ref_stu = static_cast<student &>(ref_h);

  // 访问成员也可以
  cout << "stu: m_age is " << stu->m_age << " m_id is " << stu->m_id << endl;
  cout << "ref_stu: m_age is " << ref_stu.m_age << " m_id is " << ref_stu.m_id
       << endl;

  // 利用指针访问子类对象中基类对象的成员m_age
  // cout << "m_age is " << p_h->m_age << endl;
  // 利用引用访问子类对象中基类对象的成员m_age
  // cout << "m_age is " << ref_h.m_age << endl;

  human h1;
  h1.m_age = 30;
  // 子类类型的指针指向基类类型的对象
  //  student* p = &h1;//error
  // 子类类型的引用基类对象
  //  student& ref = h1;//error
  // 利用static_case转换
  student *p = static_cast<student *>(&h1);
  student &ref = static_cast<student &>(h1);

  // 但是访问m_age是可以的,因为m_age是有效且可访问的内存
  // cout << p->m_age << endl;
  // cout << ref.m_age << endl;
  // 但是访问m_id就没有了,哪里来的m_id呢?
  // cout << p->m_id << endl;
  // cout << ref.m_id << endl;
}
