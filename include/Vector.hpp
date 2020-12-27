/// @file Vector.hpp

#ifndef VECTOR__H_
#define VECTOR__H_
/*
#ifndef COLUMN_MAJOR
#ifndef ROW_MAJOR
#define ROW_MAJOR
#endif
#endif
*/
#include <type_traits>
#ifdef VECTOR_DEBUG
#include <iostream>
#endif
#include <exception>

#ifdef VECTOR_DEBUG
static constexpr const char* const debugMessage1 = "Vector(%u) %-24s 0x%x(0x%x)\n";
static constexpr const char* const debugMessage2 = "Vector(%u) %-24s 0x%x(0x%x) to 0x%x(0x%x)\n";
#endif

/// @class Vector
template<unsigned int n, typename T>

namespace math{
    class Vector{
        private:
            T* array;                       ///< Points to the raw array of data
            mutable bool canDelete = true;  ///< Whether `delete[] array` should be called in the destructor ot not
        public:

            /**
             * @brief Allocates memory in the heap for an n-dimensional vector.
             * @note `canDelete` member is set to true as default, so the memory is going to be freed at destruction
             * @param[in] n the dimension of the vector. If 0 (default), then no space is allocated and vector is known to be null
            */
            Vector();

            /**
             * @brief Turns a single dimensional array into an n-dimensional vector.
             * @note Memory is not freed at destruction as canDelete falg is set to false
             * @param[in] array the pointer to the start of the array
            */
            Vector(const T* const array);

            /**
             * @brief Performs deep copy of data array. Thus, new memory block is allocated
             * If the datatypes don't match, each element is casted using a C-Style caste while copying.
            */
            template<typename U>
            Vector(const Vector<n,U>& vec);
            
            /**
             * @brief Reassigns raw data pointer to the new Vector object
             * 
             * If the datatypes don't match, then the data is casted using a C-style cast.
             * If the datatypes don't match ~in size~, then the data is casted and copied over
             * to the original array associated with this Vector object. 
            */
            template<typename U>
            Vector(const Vector<n,U>&& vec);

            /**
             * @brief Performs deep copy of data array.
             * If the datatypes don't match, each element is casted using a C-Style cast while copying.
            */
            template<typename U>
            void operator= (const Vector<n,U>& vec);

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
            void operator= (const Vector<n,U>&& vec);

            /// @brief Frees the raw array only if `canDelete` is true.
            ~Vector();

            
            /// @brief Returns a reference to the element in the array at index `i`.
            inline T& operator[] (const unsigned int i);

            
            /// @brief Returns a *const* reference to the element in the array at index `i`.
            inline const T& operator[] (const unsigned int i) const;

            
            /// @brief Returns the dimension of the vector.
            inline unsigned int getN() const;

            
            /// @brief Returns the raw data pointer (memeber `array`).
            inline T* getArray();

            /// @brief Returns a pointer to the raw data pointer as a pointer to *const*.
            inline const T* getArray() const;

            /// @brief Adds the 2 vectors and returns a new Vector object.
            template<unsigned int p, typename A, typename B>
            friend Vector<p,A> operator+(const Vector<p,A>& vec1, const Vector<p,B>& vec2);

            /// @brief Adds each element from the argument Vector object to each of the elements of `this`
            template<typename U>
            Vector<n,T>& operator+=(const Vector<n,U>& vec);
            
            /// @brief Subtracts the 2 vectors and returns a new Vector object.
            template<unsigned int p, typename A, typename B>
            friend Vector<p,A> operator-(const Vector<p,A>& vec1, const Vector<p,B>& vec2);

            /// @brief Subtracts each element of the argument Vector object from each of the elements of `this`
            template<typename U>
            Vector<n,T>& operator-=(const Vector<n,U>& vec);

            /// @brief Multiplies each element of `this` with `val`
            template<unsigned int p, typename A, typename B>
            friend Vector<p,A> operator*(const Vector<p,A>& vec, const B& val);

            /// @brief Multiplies each element of `this` with `val`
            template<unsigned int p, typename A, typename B>
            friend Vector<p,A> operator*(const A& val, const Vector<p,B>& vec);

            /// @brief Multiplies each element of `this` with `val`
            template<typename U>
            Vector<n,T>& operator*=(const U& val);

            /// @brief Dot Product
            template<unsigned int p, typename A, typename B>
            friend A operator* (const Vector<p,A>& vec1, const Vector<p,B>& vec2);

            /// @brief Corss Product (3 dimenstion only)
            template<typename A, typename B>
            friend Vector<3,A> xProd(const Vector<3,A>& vec1, const Vector<3,B>& vec2);

            /**
             * @brief Populates the memory block with data
             * 
             * The index of each element is passed through `func()` and
             * the result is stored in the element.
             * 
             * @note `func()` should take in *ONE `const unsigned int`* as it's parameter
             * and return a value of the template type.
             * 
             * @param[in] func The functions that indeces are passed through
            */
            template<typename F>
            void fill(F func);
    };
}

#include "../src/Vector.cpp"

#endif