
#include <Vector.hpp>

// Default Constructor
template<unsigned int n, typename T>
Vector<n,T>::Vector()
{
    array = n==0 ? nullptr : new T[n];
    #ifdef VECTOR_DEBUG
    printf(debugMessage1, n, "Ctor - default:", this, array);
    #endif
}

// Constructor overload 1
template<unsigned int n, typename T>
Vector<n,T>::Vector(const T* const array) :
    array((T*)array), canDelete(false)
{
    #ifdef VECTOR_DEBUG
    printf(debugMessage1, n, "Ctor - No Alloc:", this, array);
    #endif
}

// Copy Constructor
template<unsigned int n, typename T>
template<typename U>
Vector<n,T>::Vector(const Vector<n,U>& vec){
    array = n==0 ? nullptr : new T[n];
    for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, "Copy Ctor:", &vec, vec.array, this, array);
    #endif
}

// Move Constructor
template<unsigned int n, typename T>
template<typename U>
Vector<n,T>::Vector(const Vector<n,U>&& vec){
    #ifdef VECTOR_DEBUG
    register const char* c = "Move Ctor - Reassign:";
    #endif
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
        #ifdef VECTOR_DEBUG
        c = "Move Ctor - Copy:";
        #endif
    }
    if(!std::is_same<T,U>::value) for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i]; // Recast elements if types don's match

    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, c, &vec, vec.array, this, array);
    #endif
}

// Assign Operator
template<unsigned int n, typename T>
template<typename U>
void Vector<n,T>::operator= (const Vector<n,U>& vec){
    for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i];
    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, "Assign Op:", &vec, vec.array, this, array);
    #endif
}

// Move Operator
template<unsigned int n, typename T>
template<typename U>
void Vector<n,T>::operator= (const Vector<n,U>&& vec){
    
    #ifdef VECTOR_DEBUG
    register const char* c = "Move Op - Reassign:";
    #endif

    if(sizeof(T) == sizeof(U)){     // Reassign array if sizes match
        if(canDelete) delete[] array;
        canDelete = vec.canDelete;
        vec.canDelete = false;
        array = (T*)vec.array;
    }
    #ifdef VECTOR_DEBUG
    else c = "Move Op - Copy:";
    #endif
    if(!std::is_same<T,U>::value) for(unsigned int i = 0; i < n; i++) array[i] = (T)vec.array[i]; // Recast elements if types don't match

    #ifdef VECTOR_DEBUG
    printf(debugMessage2, n, c, &vec, vec.array, this, array);
    #endif
}

// Destructor
template<unsigned int n, typename T>
Vector<n,T>::~Vector(){
    #ifdef VECTOR_DEBUG
    register const char* c = "Dtor - No Free:";
    #endif
    if(canDelete){
        delete[] array;
        #ifdef VECTOR_DEBUG
        c = "Dtor - Mem Free:";
        #endif
    }
    #ifdef VECTOR_DEBUG
    printf(debugMessage1, n, c, this, array);
    #endif
}

// Operator []
template<unsigned int n, typename T>
inline T& Vector<n,T>::operator [](const unsigned int i){ return array[i]; }

// Operator [] const
template<unsigned int n, typename T>
inline const T& Vector<n,T>::operator [](const unsigned int i) const { return array[i]; }

// getN()
template<unsigned int n, typename T>
inline unsigned int Vector<n,T>::getN() const { return n; }

// getArray()
template<unsigned int n, typename T>
inline T* Vector<n,T>::getArray() { return array; }

// getArray() const
template<unsigned int n, typename T>
inline const T* Vector<n,T>::getArray() const { return array; }

// Operator +
template<unsigned int p, typename A, typename B>
Vector<p,A> operator+(const Vector<p,A>& vec1, const Vector<p,B>& vec2) {
    Vector<p,A> res;
    for(unsigned int i = 0; i < p; i++) res.array[i] = vec1.array[i] + (A)vec2.array[i];
    return res;
}

// Operator +=
template<unsigned int n, typename T>
template<typename U>
Vector<n,T>& Vector<n,T>::operator+=(const Vector<n,U>& vec){
    for(unsigned int i = 0; i < n; i++) array[i] += (T)vec.array[i];
    return *this;
}

// Operator -
template<unsigned int p, typename A, typename B>
Vector<p,A> operator-(const Vector<p,A>& vec1, const Vector<p,B>& vec2){
    Vector<p,A> res;
    for(unsigned int i = 0; i < p; i++) res.array[i] = vec1.array[i] - (A)vec2.array[i];
    return res;
}

// Operator -=
template<unsigned int n, typename T>
template<typename U>
Vector<n,T>& Vector<n,T>::operator-=(const Vector<n,U>& vec){
    for(unsigned int i = 0; i < n; i++) array[i] -= (T)vec.array[i];
    return *this;
}

// Operator * [scalar]
template<unsigned int p, typename A, typename B>
Vector<p,A> operator* (const Vector<p,A>& vec, const B& val){
    Vector<p,A> res;
    for(unsigned int i = 0; i < p; i++) res.array[i] = vec.array[i] * (A)val;
    return res;
}
template<unsigned int p, typename A, typename B>
Vector<p,A> operator*(const A& val, const Vector<p,B>& vec){
    Vector<p,A> res;
    for(unsigned int i = 0; i < p; i++) res.array[i] = val * (A)vec.array[i];
    return res;
}
template<unsigned int n, typename T>
template<typename U>
Vector<n,T>& Vector<n,T>::operator*=(const U& val){
    for(unsigned int i = 0; i < n; i++) array[i] *= (T)val;
    return *this;
}

template<unsigned int p, typename A, typename B>
A operator*(const Vector<p,A>& vec1, const Vector<p,B>& vec2){
    A dProd = (A)0;
    for(int i = 0; i < p; i++) dProd += vec1.array[i] * (A)vec2.array[i];
    return dProd;
}

template<typename A, typename B>
Vector<3,A> xProd(const Vector<3,A>& vec1, const Vector<3,B>& vec2){
    Vector<3,A> res;
    for()
}

// fill
template<unsigned int n, typename T>
template<typename F>
void Vector<n,T>::fill(F func){
    for(unsigned int i = 0; i < n; i++) array[i] = func(i);
}