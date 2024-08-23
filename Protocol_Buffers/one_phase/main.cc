#include "contacts.pb.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main() {
  string people_str;
  {
    tofu::peopleInfo people;
    people.set_age(26);
    people.set_name("wansghuai");
    /*对people对象进行序列化,并将序列化的数据存储到
     * string类型的对象中进行打印*/
    if (!people.SerializeToString(&people_str)) {
      cout << "序列化失败" << endl;
      return -1;
    }
    cout << "序列化的内容: " << people_str << endl;
  }
  {
    tofu::peopleInfo people;
    /*利用peopleInfo对象对数据进行反序列化*/
    if (!people.ParseFromString(people_str)) {
      cout << "反序列化失败" << endl;
    }
    cout << "序列化成功"
         << "\nname is " << people.name() << "\nage is  " << people.age()
         << endl;
  }
}
