//必须使用this参数
#include <cstring>
#include <iostream>

using namespace std;
/*前声明 告诉编译器我有这个 别给我报错*/
class human;
void print(human* argc){
  cout << "我是小石头" << endl;
}
class human {
  public:
    /*设置成员属性*/
    void set_attribute(/*human* this*/const int m_age = 20,const char *m_name = "小儿") {
      /*安全检查*/
      if(m_age < 20){
        cout << "年龄不可低于20!\n";
        exit(-1);
      }else if(!(strcmp(this->m_name, m_name))) {
        cout << "你才是小儿!\n";
        exit(-1);
      }
      /*成员属性赋值*/
      this->m_age = m_age;
      strcpy(this->m_name, m_name);
    }
    /*获取成员属性*/
    int get_age_attribute(/*human* this*/) {
      return this->m_age;
    }
    char *get_name_attribute(/*human *this*/) {
      return this->m_name;
    }
    human& return_ref_itself(/*human* this*/) {
      print(this);
      return *this;//想要返回对象自己,并使用引用对象自己作为返回值,那么是需要显式写this
    }
private:
  int m_age;
  char m_name[64];
};
int main() {
   human h1;
   h1.return_ref_itself().return_ref_itself();//串连调用
}
