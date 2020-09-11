
#include <Vector.hpp>

template<typename T>
Vector<T>::Vector(const unsigned int n):
    n(n)
{
    array = n==0 ? nullptr : new T[n];
    #ifdef VECTOR_DEBUG
    printf(debugMessage1, n, "Con - default:", this, array);
    #endif
}

template<typename T>
Vector<T>::Vector(const unsigned int n, const T* const array) :
    n(n), array((T*)array), canDelete(false)
{
    #ifdef VECTOR_DEBUG
    printf(debugMessage1, n, "Con - No Alloc:", this, array);
    #endif
}

template<typename T>
template<typename U>
Vector<T>::Vector(const Vector<U>& vec) :
    n(vec.n)
{
    array = n==0 ? nullptr : new T[n];
    for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, "Copy Con:", &vec, vec.array, this, array);
    #endif
}

template<typename T>
template<typename U>
Vector<T>::Vector(const Vector<U>&& vec) :
    n(vec.n)
{
    constexpr bool cond = (sizeof(T) == sizeof(U));
    constexpr bool flag = !(cond && std::is_same<T,U>::value);
    if(cond){                     // Reassign array if possible
        canDelete = vec.canDelete;
        vec.canDelete = false;
        array = (T*)vec.array;
        //if(std::is_same<T,U>::value) flag=0;            // If the types are the same, no need to parse each element
    }else{                                          // Else just create new array
        array = new T[vec.n];
        canDelete = true;
    }
    if(flag) for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i]; // Parse each and every element

    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, "Move Con:", &vec, vec.array, this, array);
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
    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, "Assign Op:", &vec, vec.array, this, array);
    #endif
}

template<typename T>
template<typename U>
void Vector<T>::operator= (const Vector<U>&& vec){
    constexpr bool cond = (sizeof(T) == sizeof(U));
    constexpr bool flag = !(cond && std::is_same<T,U>::value);
    if(cond){                     // Reassign array if possible
        n = vec.n;
        if(canDelete) delete[] array;
        canDelete = vec.canDelete;
        vec.canDelete = false;
        array = (T*)vec.array;
        //if(std::is_same<T,U>::value) flag = 0;            // If the types are the same, no need to parse each element
    }else{
        if(n != vec.n || !canDelete){               // Else if array can't be reused, create new array
            if(canDelete) delete[] array;
            array = new T[vec.n];
            canDelete = true;
        }
        n = vec.n;
    }
    if(flag) for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
    
    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, "Move Op:", &vec, vec.array, this, array);
    #endif
}

template<typename T>
Vector<T>::~Vector(){
    #ifdef VECTOR_DEBUG
    register const char* c = "Des - No Free:";
    #endif
    if(canDelete){
        delete[] array;
        #ifdef VECTOR_DEBUG
        c = "Des - Free Mem:";
        #endif
    }
    #ifdef VECTOR_DEBUG
    printf(debugMessage1, n, c, this, array);
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
    return res;
}

template<typename T>
inline const T* Vector<T>::getArray() const { return array; }

template<typename T>
template<typename F>
void Vector<T>::fill(F func){
    for(unsigned int i = 0; i < n; i++) array[i] = func(i);
}