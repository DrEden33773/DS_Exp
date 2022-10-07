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
#include <unordered_map>

namespace DS {

template <typename T = int> // default type = int
class DynamicArray {
private:
    T*         data     = nullptr;
    int        size     = 0;
    int        capacity = 0;
    bool       if_moved = false;
    static int init_capacity;

    /// @brief @b return_name
    virtual const char* return_name() final {
        return "Dynamic-array";
    }
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        T* ptr;
        explicit iterator(T* ptr) { this->ptr = ptr; }
        // prefix ++X/--X
        iterator operator++() {
            ++ptr;
            return *this;
        }
        iterator operator--() {
            --ptr;
            return *this;
        }
        // postfix X++/X--
        iterator operator++(int any) {
            iterator old = *this;

            operator++();
            return old;
        }
        iterator operator--(int any) {
            iterator old = *this;

            operator--();
            return old;
        }
        iterator operator+=(int n) {
            ptr += n;
            return *this;
        }
        iterator operator-=(int n) {
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
    /// @brief static constructor

    static DynamicArray<T>&& CreateDynamicArray(
        std::initializer_list<T>&& initList
    ) {
        using original_type = std::initializer_list<T>;
        DynamicArray<T> created(std::forward<original_type>(initList));
        created.if_moved = true;
        return std::move(created);
    }

    /// @brief constexpr functions

    constexpr bool if_empty() noexcept {
        return this->size == 0;
    }
    constexpr int get_length() noexcept {
        return this->size;
    }
    constexpr int get_size() noexcept {
        return this->size;
    }
    constexpr int get_capacity() noexcept {
        return this->capacity;
    }

    /// @brief object management

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
        if (!if_moved) {
            delete[] data;
        } else {
            return;
        }
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
    void pop_back() {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot pop the tail element!");
        }
        --size;
    }
    void pop() {
        pop_back();
    }

    /// @brief element operation
    /// => each input/output int is `actual index + 1` (position)!

    void insert_elem(const T& element, int pos) {
        int index = pos - 1;
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
    void insert_to(const T& element, int pos) {
        insert_elem(element, pos);
    }
    void delete_elem(int pos) {
        int index = pos - 1;
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot delete any element!");
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
    T set_elem(const T& element, int pos) {
        int index = pos - 1;
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The insert position is out of range!");
        }
        T old       = data[index];
        data[index] = element;
        return old;
    }
    T set_to(const T& element, int pos) {
        return set_elem(element, pos);
    }
    T get_elem(int pos) {
        int index = pos - 1;
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot get any element!");
        }
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The insert position is out of range!");
        }
        return data[index];
    }
    T get(int pos) {
        return get_elem(pos);
    }
    int locate_elem(const T& elem) {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot locate any element!");
        }
        int res = 0;
        for (int index = 0; index < size; ++index) {
            if (data[index] == elem) {
                res = index + 1;
                break;
            }
        }
        return res;
    }
    T prior_elem(const T& elem) {
        int elem_index = locate_elem(elem) - 1;
        if (elem_index == -1) {
            throw std::logic_error("Cannot find input element!");
        } else if (elem_index == 0) {
            throw std::logic_error(
                "The first input element lies in the head, without any prior element!"
            );
        }
        return data[elem_index - 1];
    }
    T next_elem(const T& elem) {
        int elem_index = locate_elem(elem) - 1;
        if (elem_index == -1) {
            throw std::logic_error("Cannot find input element!");
        } else if (elem_index == size - 1) {
            throw std::logic_error(
                "The first input element lies in the tail, without any next element!"
            );
        }
        return data[elem_index + 1];
    }

    /// @brief general data management

    void clear() noexcept { // ClearDynamicArray
        size = 0;
    }
    void erase() noexcept {
        size = 0;
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
        data     = tmp;
        capacity = new_capacity;
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
        data     = tmp;
        capacity = new_capacity;
    }
    void shrink_to_fit() {
        realloc(size);
    }

    /// @brief functional

    void echo() {
        std::cout << "range-based loop => ";
        for (const T& element : *this) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        // std::cout << "  old-style loop => ";
        // for (int i = 0; i < size; ++i) {
        //     std::cout << data[i] << " ";
        // }
        // std::cout << std::endl;
    }
    void std_sort() { // ascending order
        if (size == 0) {
            std::cout << return_name() << " is empty, will escape sorting. " << std::endl;
            std::cout << std::endl;
        }
        std::sort(begin(), end());
        std::cout << "Dynamic array called std::sort()" << std::endl;
        std::cout << std::endl;
    }
    void insert_sort() { // ascending order
        if (size == 0) {
            std::cout << return_name() << " is empty, will escape sorting. " << std::endl;
            std::cout << std::endl;
        }
        for (int index = 1; index < size; ++index) {
            int opt = index;
            while (opt > 0 && data[opt] < data[opt - 1]) {
                std::swap(data[opt], data[opt - 1]);
                --opt;
            }
        }
        std::cout << "Dynamic array called insert_sort()" << std::endl;
        std::cout << std::endl;
    }
    void sort(bool if_std_sort = true) { // ascending order
        if (if_std_sort) {
            std_sort();
        } else {
            insert_sort();
        }
    }
    void reverse() {
        for (int front = 0; front <= (size - 1) / 2; ++front) {
            int back = size - 1 - front;
            std::swap(data[front], data[back]); // implemented by `std::sort()`
        }
        std::cout << "Dynamic array called `reverse()`. " << std::endl;
        std::cout << std::endl;
    }
    void emplace_unique() {
        for (int index = 0; index < size; ++index) {
            T head_elem = *(begin() + index);
            for (int t_index = index + 1; t_index < size;) {
                T curr_elem = *(begin() + t_index);
                if (curr_elem == head_elem) {
                    this->delete_elem(t_index + 1);
                    // in this case, do not ++t_index
                } else {
                    ++t_index;
                }
            }
        }
    }
    void hash_unique() {
        std::unordered_map<T, bool> hash_table;
        for (int index = 0; index < size; ++index) {
            int pos       = index + 1;
            T   curr_elem = this->get_elem(pos);
            if (!hash_table.contains(curr_elem)) {
                hash_table[curr_elem] = true;
            } else if (hash_table[curr_elem]) {
                this->delete_elem(pos);
                hash_table[curr_elem] = false;
            }
        }
    }
    void unique(bool if_emplace = false) {
        if (!if_emplace) {
            hash_unique();
        } else {
            emplace_unique();
        }
    }

    /// @brief operator overloads

    T& operator[](int index) {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot get any element!");
        }
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The input index is out of range!");
        }
        return *(begin() + index);
    }
};

template <typename T>
int DynamicArray<T>::init_capacity = 4;

} // namespace DS
