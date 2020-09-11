
#define VECTOR_DEBUG

#include <Vector.hpp>
#include <iostream>

#define STRINGIFY(x) #x

template<typename T>
void printVector(const Vector<T>& vec, const char* name){
    std::cout << name << ":\n";
    for(int i = 0; i < vec.getN(); i++) std::cout << '\t' << vec[i] << '\n';
}

int main(){

    std::cout << "\n Creating Array of Vectors \n";
    Vector<int> vecs[3];
    std::cout << std::endl;

    std::cout << "\n Initializing Array of Vectors \n";
    for(int i = 0; i < 3; i++){
        vecs[i] = Vector<int>(3);
        vecs[i].fill([&](const unsigned int j){return (i+1)*j;});
    }
    std::cout << std::endl;

    std::cout << "\n Adding Vectors \n";
    Vector<int> vec = vecs[0] + vecs[1] + vecs[2];
    std::cout << std::endl;

    printVector(vecs[0], "vecs[0]");
    printVector(vecs[1], "vecs[1]");
    printVector(vecs[2], "vecs[2]");
    printVector(vec, "vec");

}
