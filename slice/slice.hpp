#pragma once

#include <iostream>
#include <stdexcept>
#include <array>
#include <vector>

template<typename T>
struct slice {
    private:
    T *ptr;
    size_t size;

    public:
    constexpr slice() : ptr(nullptr), size(0) {}
    template <size_t L>
    ///Creates slice from a std::array
    ///@param arr array
    constexpr slice(const std::array<T, L> &arr) : ptr((T*)arr.data()), size(L) {}
    ///Creates slice from a std::vector
    ///@param vec vector
    constexpr slice(const std::vector<T> &vec) : ptr((T*)vec.data()), size(vec.size()) {}
    ///Creates slice from a pointer and a sizegth
    ///@param ptr pointer
    ///@param size size
    constexpr slice(T *ptr, size_t size) : ptr(ptr), size(size) {}

    constexpr inline T &operator[](size_t i) {return ptr[i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline T &at(size_t i) {
        if(i >= size) {
            char *error = new char[
                snprintf(nullptr, 0, "the sizegth is %llu but the index is %llu", size, i)
            ];
            sprintf(error, "the sizegth is %llu but the index is %llu", size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[i];
    }
    ///Returns size
    constexpr inline size_t size() const {return size;}
    //Returns immutable pointer
    constexpr inline const T *data() const {return ptr;}
};