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

        /**
         * @brief Allocates memory in the heap for an n-dimensional vector.
         * @param[in] n the dimension of the vector. If 0 (default), then no space is allocated and vector is known to be null
        */
        Vector(const unsigned int n = 0);

        /**
         * @brief Turns a single dimensional array into an n-dimensional vector.
         * @note Memory is not freed at destruction
         * @param[in] n the dimension of the vector (size of `array`)
         * @param[in] array the pointer to the start of the array
        */
        Vector(const unsigned int n, const T* const array);

        /**
         * @brief Performs deep copy of data array.
         * If the datatypes don't match, each element is casted using a C-Style caste while copying.
        */
        template<typename U>
        Vector(const Vector<U>& vec);
        
        /**
         * @brief Reassigns raw data pointer to the new Vector object
         * If the datatypes don't match, each element is casted using a C-Style caste while copying.
         * 
        */
        template<typename U>
        Vector(const Vector<U>&& vec);

        
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
template<typename U>
Vector<T>::Vector(const Vector<U>& vec) :
    n(vec.n)
{
    array = n==0 ? nullptr : new T[n];
    for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
    #ifdef DEBUG
    printf("COPIED: %dx1 from 0x%x to 0x%x\n", n, &vec, this);
    #endif
}

template<typename T>
template<typename U>
Vector<T>::Vector(const Vector<U>&& vec) :
    n(vec.n), canDelete(vec.canDelete), array((T*)vec.array)
{
    vec.canDelete = false;
    if(!std::is_same<T,U>::value){
        if(sizeof(T) == sizeof(U))
            for(unsigned int i = 0; i < n; i++) array[i] = (T)array[i];
        else{
            array = new T[n];
            vec.canDelete = canDelete;
            canDelete = true;
            for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
        }
    }
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

/*================================================
=================== FIX ==========================
================================================*/

template<typename T>
template<typename U>
void Vector<T>::operator= (const Vector<U>&& vec){
    n = vec.n;
    array = (T*)vec.array;
    canDelete = vec.canDelete;
    vec.canDelete = false;

    if(!std::is_same<T,U>::value){
        if(sizeof(T) == sizeof(U)){
            if(canDelete) delete[] array;
            array = (T*)vec.array;
            canDelete = vec.canDelete;
            vec.canDelete = false;
            for(unsigned int i = 0; i < n; i++) array[i] = (T)array[i];
        }else{
            array = new T[n];
            canDelete = true;
            for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
        }
    }else{
        
        if(canDelete) delete[] array;
        array = (T*)vec.array;
        canDelete = vec.canDelete;
        vec.canDelete = false;
    }
    
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