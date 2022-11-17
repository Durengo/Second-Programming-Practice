#pragma once

#include <iostream>

class item
{
private:
  std::string name;
  int age;
  std::string address;
  double salary;

public:
  item(const std::string &nametemp, int agetemp, const std::string &addresstemp, double salarytemp);

  const std::string &getName() const;
  void setName(const std::string &name);

  int getAge() const;
  void setAge(int age);

  std::string getAddress() const;
  void setAddress(std::string address);

  double getSalary() const;
  void setSalary(double salary);
};