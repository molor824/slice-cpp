#pragma once

#include <iostream>
#include <stdexcept>
#include <array>
#include <vector>
#include <string>
#include <cstring>
#include <memory>
#include <initializer_list>

constexpr auto err_fmt = "the length is %llu but the index is %llu";

///A slice containing pointer and length. 
///Which can be used to pass array and vector through a function
template<typename T>
struct slice {
    private:
    const T *ptr;
    size_t _size;

    public:
    constexpr slice() : ptr(nullptr), _size(0) {}
    ///Creates slice from anything with pointer and size
    ///@param arr array, vector, string...
    template <typename T1>
    constexpr slice(const T1 &arr) : ptr(arr.data()), _size(arr.size()) {}
    ///Creates slice from an initializer list
    ///@param list initializer list
    constexpr slice(const std::initializer_list<T> &list) : ptr(list.begin()), _size(list.size()) {}
    ///Creates slice from a pointer and size
    ///@param ptr pointer
    ///@param size size
    constexpr slice(const T *ptr, const size_t size) : ptr(ptr), _size(size) {}
    ///Creates slice from char array assuming end is null terminator
    ///@param str string
    constexpr slice<const char *>(const char *str) : ptr(str), _size(strlen(str)) {}
    ///Creates slice from char array without assuming end is null terminator
    ///@param str string
    ///@param size size
    constexpr slice<const char *>(const char *str, const size_t size) : ptr(str), _size(size) {}

    ///Trims current slice
    ///@param begin begin pointer
    ///@param end end pointer
    constexpr slice<T> trim(T *begin, T *end) {
        return slice<T>(begin, (size_t)(end - begin));
    }
    ///Trims current slice
    ///@param begin begin index
    ///@param end end index
    constexpr slice<T> trim(const size_t begin, const size_t end) {
        return slice<T>((T *)data() + begin, end - begin);
    }
    ///Gets element by index. 
    ///It wont panic when index out of range which could cause segfault. 
    ///Use at() for more safer method
    ///@param i index
    ///@return Immutable reference to the element
    constexpr const T &operator[](size_t i) const {
        return ptr[i];
    }
    ///Gets element by index. 
    ///It will panic when index out of range. 
    ///@param i index
    ///@return Immutable reference to the element
    const T &at(size_t i) const {
        if(i >= _size) {
            auto err = std::unique_ptr<char []>(new char[snprintf(nullptr, 0, err_fmt, _size, i)]);

            sprintf(err.get(), err_fmt, _size, i);

            throw std::out_of_range(err.get());
        }

        return ptr[i];
    }
    ///Gets element by index. 
    ///When index out of range, it wont throw which could cause segfault. 
    ///Use at() for more safer method
    ///@param i index
    ///@return Mutable reference to the element
    constexpr T &operator[](size_t i) {
        return ptr[i];
    }
    ///Gets element by index. 
    ///When index out of range, it throws std::out_of_range
    ///@param i index
    ///@return Mutable reference to the element
    T &at(size_t i) {
        if(i >= _size) {
            auto err = std::unique_ptr<char[]>(new char[snprintf(nullptr, 0, err_fmt, _size, i)]);

            sprintf(err.get(), err_fmt, _size, i);

            throw std::out_of_range(err.get());
        }

        return ptr[i];
    }
    ///@return Size of the slice
    constexpr size_t size() const {return _size;}
    ///@return Const pointer pointing to the first element of slice
    constexpr const T *data() const {return ptr;}

    constexpr T *begin() {return ptr;}
    constexpr T *end() {return ptr + _size;}
};
template <typename T>
constexpr std::ostream &operator<<(std::ostream &os, const slice<T> &lh) {
    os << '{';

    for(size_t i = 0; i < lh.size() - 1; i++) {
        os << lh[i] << ", ";
    }

    return os << lh[lh.size() - 1] << '}';
}
