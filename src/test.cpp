
#define VECTOR_DEBUG

#include <Vector.hpp>
#include <iostream>
#include <exception>

template<typename T>
void printVector(const Vector<T>& vec, const char* name){
    std::cout << name << ":\n";
    for(int i = 0; i < vec.getN(); i++) std::cout << '\t' << vec[i] << '\n';
}

int* some(int* arg){
    return arg==(int*)7?nullptr:arg;
}

int* someOther(){
    return (int*)nullptr;
}

int main(){

    int vec1_arr[3] = {1, 2, 3};
    int vec2_arr[4] = {2, 4, 6, 7};
    int vec3_arr[3] = {5, 3, 2};

    Vector<int> vec1(3);
    Vector<int> vec2(4);
    Vector<int> vec3(3);

    memcpy(vec1.getArray(), vec1_arr, 3*sizeof(int));
    memcpy(vec2.getArray(), vec2_arr, 4*sizeof(int));
    memcpy(vec3.getArray(), vec3_arr, 3*sizeof(int));

    printVector(vec1, "vec1");
    printVector(vec2, "vec2");
    printVector(vec3, "vec3");

    try{
        (vec1+=vec2)-=vec3;
    }catch(const char* c){ std ::cout << '\n' << c << '\n' << std::endl; }

}
