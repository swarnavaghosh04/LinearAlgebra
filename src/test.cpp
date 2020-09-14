
#define VECTOR_DEBUG

#include <Vector.hpp>
#include <iostream>
#include <exception>

template<unsigned int n,typename T>
void printVector(const Vector<n,T>& vec, const char* name){
    std::cout << name << ":\n";
    for(int i = 0; i < n; i++) std::cout << '\t' << vec[i] << '\n';
}

int main(){

    int vec1_arr[3] = {1, 2, 3};
    int vec2_arr[3] = {2, 4, 6};
    int vec3_arr[3] = {5, 3, 2};

    Vector<3,int> vec1;
    Vector<3,int> vec2;
    Vector<3,int> vec3;

    memcpy(vec1.getArray(), vec1_arr, 3*sizeof(int));
    memcpy(vec2.getArray(), vec2_arr, 3*sizeof(int));
    memcpy(vec3.getArray(), vec3_arr, 3*sizeof(int));

    vec1 = vec1 * 2;

    Vector<3,int> vec4 = (vec1+vec2)-vec3;

    printVector(vec1, "vec1");
    printVector(vec2, "vec2");
    printVector(vec3, "vec3");

}
