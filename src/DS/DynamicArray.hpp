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

namespace DS {

template <typename T = int> // default type = int
class DynamicArray {
private:
    T*            data     = nullptr;
    size_t        size     = 0;
    size_t        capacity = 0;
    static size_t init_capacity;

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
        for (const T&& element : initList) {
            emplace_back(element);
        }
    }

    void push_back(const T& input) {
        if (size >= capacity) {
            realloc(capacity * 2);
        }
        data[size - 1] = input;
        ++size;
    }
    void push(const T& input) {
        push_back(input);
    }
    void emplace_back(const T& input) {
        data[size - 1] = input;
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
};

template <typename T>
size_t DynamicArray<T>::init_capacity = 4;

} // namespace DS
