// clang -Xclang -fdump-record-layouts -c main.cpp 2>&1

#include <iostream>
#include <memory>

class Animal {
public:
  virtual void spark() = 0;
  virtual ~Animal() = default;  // 虚析构函数，确保正确释放派生类对象
};

class Dog : public Animal {  // 使用 public 继承
public:
  void spark() override { std::cout << "wowoowo!" << std::endl; }
};

int main() {
  // 方法1：使用指针（需要手动释放）
  // Animal* dog = new Dog();
  // dog->spark();
  // delete dog;
  
  // 方法2：使用智能指针（推荐）
  std::unique_ptr<Animal> dog = std::make_unique<Dog>();
  dog->spark();
  
  // 方法3：使用引用（栈上对象）
  // Dog d;
  // Animal& dog = d;
  // dog.spark();
  
  return 0;
}