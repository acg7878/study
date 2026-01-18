#include <iostream>
template<typename T>
class Template {
    T value;
};  

int main() {
    Template<int> intClass;
    Template<double> doubleClass;

    if (typeid(intClass) == typeid(doubleClass)) {
        std::cout <<  "same class" << std::endl; 
    } else {
        std::cout <<  "different class" << std::endl; 
    }
}