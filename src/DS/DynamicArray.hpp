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
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>

namespace DS {

template <typename T = int> // default type = int
class DynamicArray {
private:
    T*         data     = nullptr;
    int        size     = 0;
    int        capacity = 0;
    static int init_capacity;

    class iterator : public std::iterator<std::contiguous_iterator_tag, T> {
    public:
        T* ptr;
        explicit iterator(T* ptr) { this->ptr = ptr; }
        // prefix ++X/--X
        iterator& operator++() {
            ++ptr;
            return *this;
        }
        iterator& operator--() {
            --ptr;
            return *this;
        }
        // postfix X++/X--
        iterator& operator++(int any) {
            iterator* old = *this;

            operator++();
            return old;
        }
        iterator& operator--(int any) {
            iterator* old = *this;

            operator--();
            return old;
        }
        iterator& operator+=(int n) {
            ptr += n;
            return *this;
        }
        iterator& operator-=(int n) {
            ptr -= n;
            return *this;
        }
        iterator operator+(int n) {
            iterator tmp = *this;
            tmp += n;
            return tmp;
        }
        iterator operator-(int n) {
            iterator tmp = *this;
            tmp -= n;
            return tmp;
        }
        int operator-(const iterator& rhs) { // get distance
            iterator curr     = *this;
            int      distance = curr.ptr - rhs.ptr;
            return distance;
        }
        T&   operator*() const { return *ptr; }
        T*   operator->() const { return ptr; }
        bool operator!=(const iterator& rhs) const { return ptr != rhs.ptr; }
        bool operator==(const iterator& rhs) const { return ptr == rhs.ptr; }
        bool operator>(const iterator& rhs) const { return ptr > rhs.ptr; }
        bool operator<(const iterator& rhs) const { return ptr < rhs.ptr; }
        bool operator>=(const iterator& rhs) const { return ptr >= rhs.ptr; }
        bool operator<=(const iterator& rhs) const { return ptr <= rhs.ptr; }
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

    /// @brief data_input processing

    void push_back(const T& element) {
        if (size >= capacity) {
            realloc(capacity * 2);
        }
        data[size] = element;
        ++size;
    }
    void push(const T& element) {
        push_back(element);
    }
    void emplace_back(const T& element) {
        data[size] = element;
        ++size;
    }
    void emplace(const T& element) {
        emplace_back(element);
    }
    void insert_to(const T& element, int index) {
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The insert position is out of range!");
        }
        if (index == size - 1) {
            push_back(element);
            return;
        }
        // occasion: need to move
        if (size == capacity) {
            realloc(capacity + 4); // do not need to alloc big space
        }
        int new_size = size + 1;
        for (int tmp = new_size - 1; tmp - 1 >= index; --tmp) {
            data[tmp] = data[tmp - 1];
        }
        data[index] = element;
        size        = new_size;
    }
    void insert(const T& element, int index) {
        insert_to(element, index);
    }
    void pop_back() {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot pop the tail element!");
        }
        --size;
    }
    void pop() {
        pop_back();
    }
    void delete_index(int index) {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot delete any index!");
        }
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The insert position is out of range!");
        }
        if (index == size - 1) {
            pop_back();
            return;
        }
        for (int tmp = index; tmp + 1 < size; ++tmp) {
            data[tmp] = data[tmp + 1];
        }
        --size;
    }

    /// @brief general data management

    void clear() {
        size = 0;
    }
    void erase() {
        size = 0;
    }
    void reverse() {
        for (int front = 0; front <= (size - 1) / 2; ++front) {
            int back = size - 1 - front;
            std::swap(data[front], data[back]); // implemented by `std::sort()`
        }
    }

    /// @brief memory management

    void reserve(int new_capacity) {
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
    void realloc(int new_capacity) {
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
    void shrink_to_fit() {
        realloc(size);
    }

    void echo() {
        std::cout << "range-based loop => ";
        for (const T& element : *this) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        std::cout << "  old-style loop => ";
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    void std_sort() {
        std::sort(begin(), end());
        std::cout << std::endl;
        std::cout << "Dynamic array called std::sort()" << std::endl;
        std::cout << std::endl;
    }
};

template <typename T>
int DynamicArray<T>::init_capacity = 4;

} // namespace DS
