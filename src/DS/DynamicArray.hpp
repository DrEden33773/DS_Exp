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
    T*         data     = nullptr;
    int        size     = 0;
    int        capacity = init_capacity;
    bool       if_moved = false;
    static int init_capacity;

    /// @brief @b return_name
    virtual const char* return_name() final {
        return "Dynamic-array";
    }

public:
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        T* ptr;

        constexpr explicit iterator(T* ptr)
            : ptr(ptr) { }
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
    constexpr iterator begin() {
        if (size == 0) {
            return iterator(nullptr);
        }
        return iterator(data);
    }
    constexpr iterator end() {
        if (size == 0) {
            return iterator(nullptr);
        }
        return iterator(data + size);
    }

public:
    /// @brief return the ptr of @b data
    constexpr T* return_data() {
        return data;
    }

    /// @brief static constructor

    static DynamicArray<T> CreateDynamicArray(
        std::initializer_list<T>&& initList
    ) {
        using original_type = std::initializer_list<T>;
        DynamicArray<T> created(std::forward<original_type>(initList));
        return created;
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

    DynamicArray() {
        data = new T[capacity];
    };
    DynamicArray(const DynamicArray& copied) { // copy constructor
        data     = new T[copied.capacity];
        size     = copied.size;
        capacity = copied.capacity;
        for (int i = 0; i < size; ++i) {
            data[i] = copied.data[i];
        }
    }
    DynamicArray(DynamicArray&& moved) noexcept { // move constructor
        data           = moved.data;
        size           = moved.size;
        capacity       = moved.capacity;
        moved.data     = nullptr;
        moved.size     = 0;
        moved.capacity = 0;
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
    T pop_back() {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot pop the tail element!");
        }
        T top_elem = data[size - 1];
        --size;
        return top_elem;
    }
    T pop() {
        return pop_back();
    }
    T get_back() {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot get the back element!");
        }
        return data[size - 1];
    }
    T get_front() {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot get the front element!");
        }
        return data[0];
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
        delete[] data; // old_data is trash
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
        delete[] data; // old_data is trash
        data     = tmp;
        capacity = new_capacity;
    }
    void shrink_to_fit() {
        realloc(size);
    }

    /// @brief functional

    void echo() {
        std::cout << "range-based loop => ";
        bool if_empty = true;
        for (const T& element : *this) { // this will use the iterator
            std::cout << element << " ";
            if_empty = false;
        }
        if (if_empty) {
            std::cout << "empty. ";
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
    void insert_sort(bool if_ascending = true) { // ascending order
        if (size == 0) {
            std::cout << return_name() << " is empty, will escape sorting. " << std::endl;
            std::cout << std::endl;
        }
        if (if_ascending) {
            for (int index = 1; index < size; ++index) {
                int opt = index;
                while (opt > 0 && data[opt] < data[opt - 1]) {
                    std::swap(data[opt], data[opt - 1]);
                    --opt;
                }
            }
        } else {
            for (int index = 1; index < size; ++index) {
                int opt = index;
                while (opt > 0 && data[opt] > data[opt - 1]) {
                    std::swap(data[opt], data[opt - 1]);
                    --opt;
                }
            }
        }
        std::cout << "Dynamic array called insert_sort()" << std::endl;
        std::cout << std::endl;
    }
    void sort(bool if_ascending = true) { // ascending order
        insert_sort(if_ascending);
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
    void ordered_unique() {
        DynamicArray& curr_list = *this;
        if (size == 0) { // empty list
            return;
        }
        T tmp_elem = data[0];
        for (int index = 1; index < size - 1;) {
            T curr_elem = data[index];
            if (curr_elem == tmp_elem) {
                curr_list.delete_elem(index + 1); // pos = index + 1
            } else {
                tmp_elem = curr_elem;
                ++index;
            }
        }
    }
    static void Merge_Unique(
        DynamicArray<int>& A,
        DynamicArray<int>& B
    ) {
        /// @brief this is to make sure the descending order, could escape
        A.insert_sort(false); // descending
        B.insert_sort(false); // descending

        DynamicArray<int> C = std::move(A);
        A.realloc(C.size + B.size + 8);

        int  index_C = 0;
        int  index_B = 0;
        auto data_C  = C.data;
        auto data_B  = B.data;
        while (index_C < C.size && index_B < B.size) {
            if (data_C[index_C] > data_B[index_B]) { // B < C
                int C_elem = data_C[index_C];
                A.emplace_back(C_elem);
                ++index_C;
            } else if (data_C[index_C] == data_B[index_B]) { // B == C
                int B_elem = data_B[index_B];
                A.emplace_back(B_elem);
                ++index_C;
                ++index_B;
            } else { // B > C
                int B_elem = data_B[index_B];
                A.emplace_back(B_elem);
                ++index_B;
            }
        }
        while (index_C < C.size) {
            int C_elem = data_C[index_C];
            A.emplace_back(C_elem);
            ++index_C;
        }
        while (index_B < B.size) {
            int B_elem = data_B[index_B];
            A.emplace_back(B_elem);
            ++index_B;
        }

        A.emplace_unique();
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

template <typename T>
using Vector = DynamicArray<T>;

template <typename T>
using Vec = DynamicArray<T>;

} // namespace DS
