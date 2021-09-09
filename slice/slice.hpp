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
    ///creates slice from a std::array
    ///@param arr array
    constexpr slice(const std::array<T, L> &arr) : ptr((T*)arr.data()), _size(L) {}
    ///creates slice from a std::vector
    ///@param vec vector
    constexpr slice(const std::vector<T> &vec) : ptr((T*)vec.data()), _size(vec.size()) {}
    ///creates slice from a pointer and a length
    ///@param ptr pointer
    ///@param size size
    constexpr slice(T *ptr, size_t size) : ptr(ptr), _size(size) {}

    ///gets element in the given index
    ///wont panic when index out of range which could cause segfault
    ///use at() if you want more safer method
    ///@param i index
    ///@return immutable reference to the element(for mutable reference, get from mutable slice)
    constexpr inline const T &operator[](size_t i) const {
        return ptr[i];
    }
    ///gets element in the given index
    ///it will panic when index out of range
    ///@param i index
    ///@return immutable reference to the element(for mutable reference, get from mutable slice)
    constexpr const T &at(size_t i) const {
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
    ///gets element in the given index
    ///wont panic when index out of range which could cause segfault
    ///use at() if you want more safer method
    ///@param i index
    ///@return mutable reference to the element(for immutable reference, get from immutable slice)
    constexpr inline T &operator[](size_t i) {
        return ptr[i];
    }
    ///gets element in the given index
    ///it will panic when index out of range
    ///@param i index
    ///@return mutable reference to the element(for immutable reference, get from immutable slice)
    constexpr T &at(size_t i) {
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
    ///@return size of the slice
    constexpr inline size_t size() const {return _size;}
    ///@return size of the slice
    constexpr inline const T *data() const {return ptr;}

    constexpr inline T *begin() {return ptr;}
    constexpr inline T *end() {return ptr + _size;}
};
