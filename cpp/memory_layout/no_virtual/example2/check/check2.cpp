#include <iostream>
#include <string>
class Animal {
  int age;
};
class Dog : public Animal {
  std::string name;
};

// 地址重合优化
int main() {
  Animal* dog_ptr_as_animal = new Dog();
  Dog* dog_ptr = static_cast<Dog*>(dog_ptr_as_animal);
  std::cout << "Address of Animal pointer: " << dog_ptr_as_animal << std::endl;
  std::cout << "Address of Dog pointer:    " << dog_ptr << std::endl;
}