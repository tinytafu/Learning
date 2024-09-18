#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
class human{
  public:
    human(int const age = 10,string const name = "无名"):age_{age},name_{name}{
      cout << "human(int,string)" << endl;
    }
    ~human(){
      cout << "~human()" << endl;
    }
    friend std::ostream& operator<<(std::ostream &os,human const &that);
  private:
    int age_;
    string name_;
};
std::ostream& operator<<(std::ostream &os,human const &that){
  os << "name: " << that.name_ << endl << "age: " << that.age_;
  return os;
}
int main (){
  human h1(20,"wangshuai");
  cout << h1 << endl;
}
