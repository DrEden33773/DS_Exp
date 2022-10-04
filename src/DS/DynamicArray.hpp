/**
 * @file DynamicArray.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief An implementation of DynamicArray (=> std::vector)
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>

namespace DS {

template <typename T = int> // default type = int
class DynamicArray {
private:
    T*            data     = nullptr;
    size_t        size     = 0;
    size_t        capacity = 0;
    static size_t init_capacity;

    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        T* ptr;
        explicit iterator(T* ptr) { this->ptr = ptr; }
        iterator& operator++() {
            ++ptr;
            return *this;
        }
        iterator& operator--() {
            --ptr;
            return *this;
        }
        iterator& operator+=(size_t n) {
            ptr += n;
            return *this;
        }
        iterator& operator-=(size_t n) {
            ptr -= n;
            return *this;
        }
        iterator operator+(size_t n) {
            iterator tmp = *this;
            tmp += n;
            return tmp;
        }
        iterator operator-(size_t n) {
            iterator tmp = *this;
            tmp -= n;
            return tmp;
        }
        T&   operator*() { return *ptr; }
        T*   operator->() { return ptr; }
        bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }
        bool operator>(const iterator& rhs) { return ptr > rhs.ptr; }
        bool operator<(const iterator& rhs) { return ptr < rhs.ptr; }
        bool operator>=(const iterator& rhs) { return ptr >= rhs.ptr; }
        bool operator<=(const iterator& rhs) { return ptr <= rhs.ptr; }
        // do not use `operator==` , it will cause infinite loop (ambiguous)
    };
    iterator begin() {
        if (size == 0) {
            return iterator(nullptr);
        }
        return iterator(data);
    }
    iterator end() {
        if (size == 0) {
            return iterator(nullptr);
        }
        return iterator(data + size);
    }

public:
    DynamicArray() = default;
    DynamicArray(const DynamicArray& copied) { // copy constructor
        data     = new T[copied.capacity];
        size     = copied.size;
        capacity = copied.capacity;
        for (int i = 0; i < size; ++i) {
            data[i] = copied.data[i];
        }
    }
    DynamicArray(DynamicArray&& moved) noexcept { // move constructor
        data       = moved.data;
        size       = moved.size;
        capacity   = moved.capacity;
        moved.data = nullptr;
    }
    DynamicArray(std::initializer_list<T>&& initList) {
        reserve(initList.size() * 2);
        for (const T& element : initList) {
            emplace_back(element);
        }
    }
    ~DynamicArray() {
        delete[] data;
    }

    void push_back(const T& input) {
        if (size >= capacity) {
            realloc(capacity * 2);
        }
        data[size] = input;
        ++size;
    }
    void push(const T& input) {
        push_back(input);
    }
    void emplace_back(const T& input) {
        data[size] = input;
        ++size;
    }
    void emplace(const T& input) {
        emplace_back(input);
    }
    void reserve(size_t new_capacity) {
        if (new_capacity < capacity) {
            std::cout << std::endl;
            std::cout << "new_capacity " << new_capacity;
            std::cout << " is smaller than current capacity " << capacity << " . ";
            std::cout << "func reserve() won't be execute. ";
            std::cout << std::endl;
            return;
        } // new_capacity >= capacity >= size
        T* tmp = new T[new_capacity];
        for (int i = 0; i < size; ++i) {
            tmp[i] = data[i];
        }
        data = tmp;
    }
    void realloc(size_t new_capacity) {
        if (new_capacity < size) {
            std::cout << std::endl;
            std::cout << "new_capacity " << new_capacity;
            std::cout << " is smaller than current size " << size << " . ";
            std::cout << "func realloc() won't be execute. ";
            std::cout << std::endl;
            return;
        } // new_capacity >= size
        T* tmp = new T[new_capacity];
        for (int i = 0; i < size; ++i) {
            tmp[i] = data[i];
        }
        data = tmp;
    }

    void echo() {
        std::cout << "range-based `for loop` => ";
        for (const T& element : *this) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        std::cout << "  old-style `for loop` => ";
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    void std_sort() {
        // TODO(eden):
    }
};

template <typename T>
size_t DynamicArray<T>::init_capacity = 4;

} // namespace DS
