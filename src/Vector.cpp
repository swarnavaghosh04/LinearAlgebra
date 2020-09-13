
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
    /*
    if T and U have the same size, then reassign vec.array to `this->array`
    else allocate new array to `this->array`
    if T and U are not the same type, then loop through `this->array` and cast each element to T 
    */
    if(sizeof(T) == sizeof(U)){     // Reassign array if sizes match
        canDelete = vec.canDelete;
        vec.canDelete = false;
        array = (T*)vec.array;
    }else{                          // Else just create new array
        array = n==0 ? nullptr : new T[n];
        canDelete = true;
    }
    if(!std::is_same<T,U>::value) for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i]; // Recast elements if types don's match

    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, "Move Con:", &vec, vec.array, this, array);
    #endif
}

template<typename T>
template<typename U>
void Vector<T>::operator= (const Vector<U>& vec){
    if(n != vec.n){
        if(canDelete) delete[] array;
        array = vec.n==0 ? nullptr : new T[vec.n];
    }
    n = vec.n;
    for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, "Assign Op:", &vec, vec.array, this, array);
    #endif
}

/*=====================================================
======================= FIX ===========================
=====================================================*/

template<typename T>
template<typename U>
void Vector<T>::operator= (const Vector<U>&& vec){
    
    if(sizeof(T) == sizeof(U)){     // Reassign array if sizes match
        canDelete = vec.canDelete;
        vec.canDelete = false;
        array = (T*)vec.array;
    }else{                          // Else just create new array
        array = (n==vec.n ? array : (vec.n==0 ? nullptr : new T[vec.n]));
        canDelete = true;
    }
    n = vec.n;
    if(!std::is_same<T,U>::value) for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i]; // Recast elements if types don's match

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
template<typename U>
Vector<T>& Vector<T>::operator+=(const Vector<U>& vec){
    if(n != vec.n) throw "[Error] Input Vectors have different dimensions, and therefore operation `+=` cannot be performed";
    for(int i = 0; i < n; i++) array[i] += (T)vec.array[i];
    return *this;
}

template<typename T>
template<typename U>
Vector<T> Vector<T>::operator-(const Vector<U>& vec) const{
    if(n != vec.n) return Vector<T>(0);
    Vector<T> res(n);
    for(int i = 0; i < n; i++) res[i] = array[i] - vec[i];
    return res;
}

template<typename T>
template<typename U>
Vector<T>& Vector<T>::operator-=(const Vector<U>& vec){
    if(n != vec.n) throw "[Error] Input Vectors have different dimensions, and therefore operation `-=` cannot be performed";
    for(int i = 0; i < n; i++) array[i] -= (T)vec.array[i];
    return *this;
}

template<typename T>
inline const T* Vector<T>::getArray() const { return array; }

template<typename T>
template<typename F>
void Vector<T>::fill(F func){
    for(unsigned int i = 0; i < n; i++) array[i] = func(i);
}