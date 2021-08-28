#pragma once

#include <iostream>
#include <stdexcept>
#include <array>
#include <vector>

template<typename T>
struct slice {
    private:
    T *ptr;
    size_t len;

    public:
    constexpr slice() : ptr(nullptr), len(0) {}
    template <size_t L>
    constexpr slice(const std::array<T, L> &arr) : ptr((T*)arr.data()), len(L) {}
    constexpr slice(const std::vector<T> &vec) : ptr((T*)vec.data()), len(vec.size()) {}
    constexpr slice(T *ptr, size_t len) : ptr(ptr), len(len) {}

    constexpr inline T &operator[](size_t i) {return ptr[i];}
    constexpr inline T &at(size_t i) {
        if(i >= len) {
            char *error = new char[
                snprintf(nullptr, 0, "the length is %llu but the index is %llu", len, i)
            ];
            sprintf(error, "the length is %llu but the index is %llu", len, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[i];
    }
    constexpr inline size_t size() const {return len;}
    constexpr inline const T *data() const {return ptr;}
};