#include <iostream>
class Animal {};
class Dog : public Animal {};

// 用这个命令查看内存分布
// clang++ -Xclang -fdump-record-layouts .\example1.cpp -o .output\example1  >> info.txt

// Dog 触发空基类优化，复用Animal的一字节空间，所以它也是一字节

int main() {
  Animal* dog = new Dog();
  std::cout << "Animal:" << sizeof(Animal) << std::endl;
  std::cout << "Dog   :" << sizeof(Dog) << std::endl;
}