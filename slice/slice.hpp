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
    ///Creates slice from a pointer and a size
    ///@param ptr pointer
    ///@param size size
    constexpr slice(T *ptr, size_t size) : ptr(ptr), _size(size) {}

    constexpr inline T &operator[](size_t i) {return ptr[i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline T &at(size_t i) {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[i];
    }
    constexpr inline T &operator[](long long i) {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline T &at(long long i) {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    constexpr inline T &operator[](int i) {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline T &at(int i) {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    constexpr inline T &operator[](unsigned int i) {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline T &at(unsigned int i) {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    constexpr inline T &operator[](long i) {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline T &at(long i) {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    constexpr inline T &operator[](unsigned long i) {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline T &at(unsigned long i) {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }

    constexpr inline const T &operator[](size_t i) const {return ptr[i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline const T &at(size_t i) const {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[i];
    }
    constexpr inline const T &operator[](long long i) const {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline const T &at(long long i) const {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    constexpr inline const T &operator[](int i) const {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline const T &at(int i) const {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    constexpr inline const T &operator[](unsigned int i) const {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline const T &at(unsigned int i) const {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    constexpr inline const T &operator[](long i) const {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline const T &at(long i) const {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    constexpr inline const T &operator[](unsigned long i) const {return ptr[(size_t)i];}
    ///Simular to operator[] except it throws error when index is out of range
    ///@param i index
    constexpr inline const T &at(unsigned long i) const {
        if(i >= _size) {
            char *error = new char[
                snprintf(nullptr, 0, "the size is %llu but the index is %llu", _size, i)
            ];
            sprintf(error, "the size is %llu but the index is %llu", _size, i);

            throw std::out_of_range(error);

            delete[] error;
        }
        
        return ptr[(size_t)i];
    }
    ///Returns size
    constexpr inline size_t size() const {return _size;}
    //Returns immutable pointer
    constexpr inline const T *data() const {return ptr;}

    constexpr inline T *begin() {return ptr;}
    constexpr inline T *end() {return ptr + _size;}
};