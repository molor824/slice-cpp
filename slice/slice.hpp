#pragma once

#include <iostream>
#include <stdexcept>
#include <array>
#include <vector>
#include <string>
#include <cstring>
#include <memory>

///A slice containing pointer and length. 
///Which can be used to pass array and vector through a function
template<typename T>
struct slice {
    private:
    T *ptr;
    size_t _size;

    public:
    constexpr inline slice() : ptr(nullptr), _size(0) {}
    template <size_t L>
    ///Creates slice from a std::array
    ///@param arr array
    constexpr inline slice(const std::array<T, L> &arr) : ptr((T *)arr.data()), _size(L) {}
    ///Creates slice from a std::vector
    ///@param vec vector
    constexpr inline slice(const std::vector<T> &vec) : ptr((T *)vec.data()), _size(vec.size()) {}
    ///Creates slice from a pointer and a length
    ///@param ptr pointer
    ///@param size size
    constexpr inline slice(T *ptr, const size_t size) : ptr(ptr), _size(size) {}
    ///Creates slice from a string
    ///@param str string
    constexpr inline slice<std::string>(const std::string &str) : ptr((T *)str.data()), _size(str.size()) {}
    ///Creates slice from a string
    ///@param str string
    constexpr inline slice<const char *>(const char *str) : ptr((T *)str), _size(strlen(str)) {}

    ///Trims current slice
    ///@param begin begin pointer
    ///@param end end pointer
    constexpr inline slice<T> trim(T *begin, T *end) {
        return slice<T>(begin, (size_t)(end - begin));
    }
    ///Trims current slice
    ///@param begin begin index
    ///@param end end index
    constexpr inline slice<T> trim(const size_t begin, const size_t end) {
        return slice<T>((T *)data() + begin, end - begin);
    }
    ///Gets element by index. 
    ///It wont panic when index out of range which could cause segfault. 
    ///Use at() for more safer method
    ///@param i index
    ///@return Immutable reference to the element
    constexpr inline const T &operator[](size_t i) const {
        return ptr[i];
    }
    ///Gets element by index. 
    ///It will panic when index out of range. 
    ///@param i index
    ///@return Immutable reference to the element
    const T &at(size_t i) const {
        if(i >= _size) {
            auto fmt = "index out of range: the length is %llu but the index is %llu";
            auto err = std::unique_ptr<char []>(new char[snprintf(nullptr, 0, fmt, _size, i)]);

            sprintf(err.get(), fmt, _size, i);

            throw std::out_of_range(err.get());
        }

        return ptr[i];
    }
    ///Gets element by index. 
    ///When index out of range, it wont throw which could cause segfault. 
    ///Use at() for more safer method
    ///@param i index
    ///@return Mutable reference to the element
    constexpr inline T &operator[](size_t i) {
        return ptr[i];
    }
    ///Gets element by index. 
    ///When index out of range, it throws std::out_of_range
    ///@param i index
    ///@return Mutable reference to the element
    T &at(size_t i) {
        if(i >= _size) {
            auto fmt = "the length is %llu but the index is %llu";
            auto err = std::unique_ptr<char[]>(new char[snprintf(nullptr, 0, fmt, _size, i)]);

            sprintf(err.get(), fmt, _size, i);

            throw std::out_of_range(err.get());
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
template <typename T>
constexpr std::ostream &operator<<(std::ostream &os, const slice<T> &lh) {
    os << '{';

    for(size_t i = 0; i < lh.size() - 1; i++) {
        os << lh[i] << ", ";
    }

    return os << lh[lh.size() - 1] << '}';
}
