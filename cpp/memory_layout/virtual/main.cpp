class Animal {
  virtual void spark() = 0;
  int age;
};

class Dog : public Animal {
  void spark() {}
};

int main() {
  Animal* dog = new Dog();
}