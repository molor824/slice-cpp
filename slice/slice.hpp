#pragma once

#include <iostream>
#include <stdexcept>
#include <array>
#include <vector>

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
    constexpr slice(T *ptr, std::size_t size) : ptr(ptr), _size(size) {}

    ///Gets element in the given index
    ///It will panic when tries to access index out of range
    ///@param i index
    constexpr T &operator[](std::size_t i) {
        if(i >= _size) {
            const char *fmt = "index out of range: the length is %llu but the index is %llu";
            char *err = new char[snprintf(nullptr, 0, fmt, _size, i)];
            sprintf(err, fmt, _size, i);

            fprintf(stderr, "error: '%s'\n", err);

            delete[] err;
            exit(-1);
        }

        return ptr[i];
    }
    ///Returns size
    constexpr inline size_t size() const {return _size;}
    ///Returns immutable pointer
    constexpr inline const T *data() const {return ptr;}

    constexpr inline T *begin() {return ptr;}
    constexpr inline T *end() {return ptr + _size;}
};
