
#define DEBUG

#include <Vector.hpp>
#include <iostream>

#define STRINGIFY(x) #x

void printVector(const Vector<float>& vec, const char* name){
    std::cout << name << ":\n";
    for(int i = 0; i < vec.getN(); i++) std::cout << '\t' << vec[i] << '\n';
}

int main(){
    Vector<float> vec1(3);
    vec1.fill([](const unsigned int i){ return 2.f*i; });
    Vector<float> vec2(3);
    vec2.fill([](const unsigned int i){ return 1.f*i; });
    Vector<float> vec3;
    vec3 = vec1 + vec2;
    printVector(vec1, STRINGIFY(vec1));
    printVector(vec2, STRINGIFY(vec2));
    printVector(vec3, STRINGIFY(vec3));
    std::cout << vec3.getArray() << std::endl;
}
