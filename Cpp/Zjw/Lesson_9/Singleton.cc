// 饿汉式 单例模式

class singleton {
public:
  static singleton &get_instance() { return instance; }

private:
  singleton() {}
  singleton(const singleton &that) {}
  static singleton instance;
};

singleton singleton::instance;

int main() { singleton &s1 = singleton::get_instance(); }
