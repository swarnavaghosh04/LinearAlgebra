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

#ifdef VECTOR_DEBUG
static constexpr const char* const debugMessage1 = "Vector(%u) %-20s 0x%x(0x%x)\n";
static constexpr const char* const debugMessage2 = "Vector(%u) %-20s 0x%x(0x%x) to 0x%x(0x%x)\n";
#endif

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
         * @note `canDelete` member is set to true as default, so the memory is going to freed at destruction
         * @param[in] n the dimension of the vector. If 0 (default), then no space is allocated and vector is known to be null
        */
        Vector(const unsigned int n = 0);

        /**
         * @brief Turns a single dimensional array into an n-dimensional vector.
         * @note Memory is not freed at destruction as canDelete falg is set to false
         * @param[in] n the dimension of the vector (size of `array`)
         * @param[in] array the pointer to the start of the array
        */
        Vector(const unsigned int n, const T* const array);

        /**
         * @brief Performs deep copy of data array. Thus, new memory block is allocated
         * If the datatypes don't match, each element is casted using a C-Style caste while copying.
        */
        template<typename U>
        Vector(const Vector<U>& vec);
        
        /**
         * @brief Reassigns raw data pointer to the new Vector object
         * 
         * If the datatypes don't match, each element is casted using a C-Style caste while copying.
         * 
         * A new memory block is allocated only if the size of the datatypes are not the same.
         * In that case, `canDelete` is set to true. Otherwise, the value of `canDelete` is inherited from
         * the parameter Vector object.
        */
        template<typename U>
        Vector(const Vector<U>&& vec);

        /**
         * @brief Performs deep copy of data array.
         * If the datatypes don't match, each element is casted using a C-Style cast while copying.
         * A new memory block is not allocated if the size of the orignial `this->array` can fit the new data exactly (when vec.n == this->n).
        */
        template<typename U>
        void operator= (const Vector<U>& vec);

        /**
         * @brief 
        */
        template<typename U>
        void operator= (const Vector<U>&& vec);
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

#include "../src/Vector.cpp"

#endif