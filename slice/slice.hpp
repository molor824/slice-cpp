#pragma once

#include <iostream>
#include <stdexcept>
#include <array>
#include <vector>

///A slice containing pointer and length. 
///Which can be used to pass array and vector through a function
template<typename T>
struct slice {
    private:
    T *ptr;
    size_t _size;

    public:
    constexpr slice() : ptr(nullptr), _size(0) {}
    template <size_t L>
    ///Creates slice from a std::array
    ///@param arr array
    constexpr slice(const std::array<T, L> &arr) : ptr((T*)arr.data()), _size(L) {}
    ///Creates slice from a std::vector
    ///@param vec vector
    constexpr slice(const std::vector<T> &vec) : ptr((T*)vec.data()), _size(vec.size()) {}
    ///Creates slice from a pointer and a length
    ///@param ptr pointer
    ///@param size size
    constexpr slice(T *ptr, size_t size) : ptr(ptr), _size(size) {}

    ///Gets element by index. 
    ///It wont panic when index out of range which could cause segfault. 
    ///Use at() for more safer method
    ///@param i index
    ///@return Immutable reference to the element
    constexpr inline const T &operator[](size_t i) const {
        return ptr[i];
    }
    ///Gets elemeny by index. 
    ///It will panic when index out of range
    ///@param i index
    ///@return Immutable reference to the element
    constexpr const T &at(size_t i) const {
        if(i >= _size) {
            const char *fmt = "index out of range: the length is %llu but the index is %llu";
            char *err = new char[snprintf(nullptr, 0, fmt, _size, i)];
            sprintf(err, fmt, _size, i);
            
            throw std::out_of_range(err);

            delete[] err;
        }

        return ptr[i];
    }
    ///Gets element by index. 
    ///When index out of range, it wont throw which could cause segfault. 
    ///Use at() for more safer method
    ///@param i index
    ///@return Immutable reference to the element
    constexpr inline T &operator[](size_t i) {
        return ptr[i];
    }
    ///Gets elemeny by index. 
    ///When index out of range, it throws std::out_of_range
    ///@param i index
    ///@return Immutable reference to the element
    constexpr T &at(size_t i) {
        if(i >= _size) {
            const char *fmt = "index out of range: the length is %llu but the index is %llu";
            char *err = new char[snprintf(nullptr, 0, fmt, _size, i)];
            sprintf(err, fmt, _size, i);
            
            throw std::out_of_range(err);

            delete[] err;
        }

        return ptr[i];
    }
    ///@return Size of the slice
    constexpr inline size_t size() const {return _size;}
    ///@return Const pointer pointing to the first element of slice
    constexpr inline const T *data() const {return ptr;}

    constexpr inline T *begin() {return ptr;}
    constexpr inline T *end() {return ptr + _size;}
};
