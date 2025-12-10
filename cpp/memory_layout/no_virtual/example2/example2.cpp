class Animal {
    int age;
};
class Dog : public Animal {};


int main() {
  Animal* dog = new Dog();
}