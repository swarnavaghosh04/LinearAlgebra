/// @file Vector.hpp

#ifndef VECTOR__H_
#define VECTOR__H_

#ifndef COLUMN_MAJOR
#ifndef ROW_MAJOR
#define ROW_MAJOR
#endif
#endif

#include <type_traits>
#include <iostream>

/// @class Vector
template<typename T>
class Vector{
        template<typename U>
        friend class Vector;
    private:
        T* array;                       ///< Points to the raw array of data
        unsigned int n;                 ///< The dimension of the vector (the number of indeces)
        mutable bool canDelete = true;  ///< Whether `delete[] array` should be called in the destructor ot not
    public:
        Vector(const unsigned int n = 0);
        Vector(const unsigned int n, const T* const array);
        Vector(const Vector<T>& vec);
        Vector(const Vector<T>&& vec);
        template<typename U>
        void operator = (const Vector<U>& vec);
        template<typename U>
        void operator = (const Vector<U>&& vec);
        ~Vector();
        inline T& operator[] (const unsigned int i);
        inline const T& operator[] (const unsigned int i) const;
        inline unsigned int getN() const;
        inline T* getArray();
        inline const T* getArray() const;
        template<typename U>
        Vector<T> operator+ (const Vector<U>& vec2) const;
        template<typename F>
        void fill(F func);
};

template<typename T>
Vector<T>::Vector(const unsigned int n):
    n(n)
{
    array = n==0 ? nullptr : new T[n];
    #ifdef DEBUG
    printf("CONSTRUCTED: %dx1 @ 0x%x\n", n, this);
    #endif
}

template<typename T>
Vector<T>::Vector(const unsigned int n, const T* const array) :
    n(n), array((T*)array), canDelete(false)
{
    #ifdef DEBUG
    printf("CONSTRUCTED: %dx1 @ 0x%x (no alloc)\n", n, this);
    #endif
}

template<typename T>
Vector<T>::Vector(const Vector<T>& vec) :
    n(vec.n)
{
    array = n==0 ? nullptr : new T[n];
    for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
    #ifdef DEBUG
    printf("COPIED: %dx1 from 0x%x to 0x%x\n", n, &vec, this);
    #endif
}

template<typename T>
Vector<T>::Vector(const Vector<T>&& vec) :
    n(vec.n), canDelete(vec.canDelete), array(vec.array)
{
    vec.canDelete = false;
    #ifdef DEBUG
    printf("CONSTRUCTED: %dx1 from 0x%x to 0x%x\n", n, &vec, this);
    #endif
}

template<typename T>
template<typename U>
void Vector<T>::operator= (const Vector<U>& vec){
    if(n != vec.n){
        n = vec.n;
        if(canDelete) delete[] array;
        array = n==0 ? nullptr : new T[n];
    }
    for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
    #ifdef DEBUG
    printf("ASSIGNED: %dx1 from 0x%x to 0x%x\n", n, &vec, this);
    #endif
}

template<typename T>
template<typename U>
void Vector<T>::operator= (const Vector<U>&& vec){
    if(canDelete) delete[] array;
    n = vec.n;
    array = (T*)vec.array;
    canDelete = vec.canDelete;
    vec.canDelete = false;
    if(!std::is_same<T,U>::value)
        for(unsigned int i = 0; i < n; i++) array[i] = (T)array[i];
    #ifdef DEBUG
    printf("MOVED: %dx1 from 0x%x to 0x%x\n", n, &vec, this);
    #endif
}

template<typename T>
Vector<T>::~Vector(){
    if(canDelete) delete[] array;
    #ifdef DEBUG
    printf("DESTROYED: %dx1 @ 0x%x\n", n, this);
    #endif
}

template<typename T>
inline T& Vector<T>::operator[](const unsigned int i){ return array[i]; }

template<typename T>
inline const T& Vector<T>::operator[](const unsigned int i) const { return array[i]; }

template<typename T>
inline unsigned int Vector<T>::getN() const { return n; }

template<typename T>
inline T* Vector<T>::getArray() { return array; }

template<typename T>
template<typename U>
Vector<T> Vector<T>::operator+(const Vector<U>& vec) const{
    if(n != vec.n) return Vector<T>(0);
    Vector<T> res(n);
    for(int i = 0; i < n; i++) res[i] = array[i] + vec[i];
    std::cout << res.array << std::endl;
    return res;
}

template<typename T>
inline const T* Vector<T>::getArray() const { return array; }

template<typename T>
template<typename F>
void Vector<T>::fill(F func){
    for(unsigned int i = 0; i < n; i++) array[i] = func(i);
}

#endif