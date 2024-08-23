#include "contacts.pb.h"
#include <fstream>
#include <google/protobuf/stubs/common.h>
#include <iostream>
#include <string>
using namespace std;

void addPeopleInfo(tofu::peopleInfo *people) {
  cout << "----------新增一个联系人----------" << endl;
  cout << "请输入联系人的姓名: " << endl;
  string name;
  getline(cin, name);
  people->set_name(name);
  cout << "请输入联系人的年龄: " << endl;
  int age;
  cin >> age;
  people->set_age(age);
  // 清空缓冲区
  cin.ignore(256, '\n');
  int count = 1;
  while (1) {
    cout << "请输入联系人电话" << count << "(只输入回车完成电话新增)" << endl;
    string number;
    getline(cin, number);
    if (number.empty())
      break;
    tofu::peopleInfo::phone *phone_number = people->add_phone_numbers();
    phone_number->set_numbers(number);
  }

  cout << "----------添加联系人成功----------" << endl;
}
int main() {
  GOOGLE_PROTOBUF_VERSION;
  // 先要检查是否存在需要写入的二进制文件
  // 如果存在则先读取已存在的contacts.bin

  // 创建一个contacts
  tofu::contact contacts;
  fstream input("contacts.bin", ios::in | ios::binary);
  // 如果不存在,则创建一个新的二进制文件
  if (!input) {
    cout << "file not found. Creating a new file!\n";
    // 如果存在,则对此文件输入流对象进行反序列化
  } else if (!contacts.ParseFromIstream(&input)) {
    cout << "failed to parse contacts!\n";
    input.close();
    return -1;
  }

  // 添加一个新的联系人
  addPeopleInfo(contacts.add_people_info());

  // 将contacts对象序列化写入到二进制文件
  // 创建一个文件输出流对象,如果存在则清空
  fstream output("contacts.bin", ios::out | ios::trunc | ios::binary);
  if (!contacts.SerializeToOstream(&output)) {
    cerr << "failed to write contacts\n";
    input.close();
    output.close();
    return -1;
  }
  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}
