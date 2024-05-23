#ifndef HUMAN_H
#define HUMAN_H

class human {
public:
  human(int m_age = 10, const char *m_name = "无名");
  void getinfo() const;

private:
  int m_age;
  char m_name[64];
};

#endif
