/**
 * @file SingleList.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Linked list with only one pointer
 * @structure:
        head->[data|ptr]->[data|ptr]->...->[data|ptr]-> nullptr
                                            ^^^^------> tail
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
#include <stdexcept>

namespace DS {

template <typename T = int> // default type = int
class SingleList {
private:
    struct node {
        T     element;
        node* next = nullptr;
        node()     = default;
        explicit node(const T& element) { this->element = element; }
    };
    node* head    = nullptr; // head node never maintain data
    node* tail    = nullptr; // tail node always maintain data
    bool  if_init = false;   // if init head node
    int   size    = 0;       // num of nodes (except head node)
                             // (num of effective nodes)

    /// @brief iterator (input_iterator)
    class iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        node* ptr = nullptr;
        explicit iterator(node* ptr) { this->ptr = ptr; }
        iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        iterator& operator+(int distance) {
            iterator res = *this;
            if (distance > 0) {
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->next;
                }
            } else if (distance < 0) { // change to the abs value
                distance *= -1;
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->next;
                }
            }
            return res;
        }
        int operator-(const iterator& rhs) {
            // assume that `rhs` -> ... -> `lhs`
            int distance = 0;
            for (node* curr = ptr; ptr != rhs.ptr; ptr = ptr->next) {
                ++distance;
            }
            return distance;
        }

        T&   operator*() const { return ptr->element; }
        T*   operator->() const { return &(ptr->element); }
        bool operator!=(const iterator& rhs) const { return ptr != rhs.ptr; }
        bool operator==(const iterator& rhs) const { return ptr == rhs.ptr; }
        bool operator>(const iterator& rhs) const {
            return SingleList::if_A_behind_B(this->ptr, rhs.ptr);
        }
        bool operator>=(const iterator& rhs) const {
            bool behind = SingleList::if_A_behind_B(this->ptr, rhs.ptr);
            bool eq     = SingleList::if_A_is_B(this->ptr, rhs.ptr);
            return behind || eq;
        }
        bool operator<(const iterator& rhs) const {
            return SingleList::if_A_ahead_B(this->ptr, rhs.ptr);
        }
        bool operator<=(const iterator& rhs) const {
            bool ahead = SingleList::if_A_ahead_B(this->ptr, rhs.ptr);
            bool eq    = SingleList::if_A_is_B(this->ptr, rhs.ptr);
            return ahead || eq;
        }
    };
    iterator begin() {
        return iterator(head->next);
    }
    iterator end() {
        return iterator(tail->next);
    }

    /// @brief relative location relation resolver

    static constexpr bool if_A_ahead_B(node* A, node* B) {
        bool  res = false;
        node* tmp = A;
        while (tmp != nullptr) {
            if (tmp == B) {
                res = true;
                break;
            }
            tmp = tmp->next;
        }
        return res;
    }
    static constexpr bool if_A_behind_B(node* A, node* B) {
        bool  res = false;
        node* tmp = B;
        while (tmp != nullptr) {
            if (tmp == A) {
                res = true;
                break;
            }
            tmp = tmp->next;
        }
        return res;
    }
    static constexpr bool if_A_is_B(node* A, node* B) {
        return A == B;
    }
    static constexpr bool if_A_is_not_B(node* A, node* B) {
        return A != B;
    }

public:
    /// @brief object management

    SingleList() { // default constructor (not recommended!)
        init_head();
    }
    SingleList(const SingleList& copied) { // copy constructor
        init_head();
    }
    SingleList(SingleList&& moved) noexcept { // move constructor
        // 1. guarantee `this`
        node* curr      = head;
        node* tmp_moved = moved.head;
        while (curr != nullptr) {
            curr                 = tmp_moved;
            curr                 = curr->next;
            node* tmp_moved_next = tmp_moved->next;
            tmp_moved            = nullptr;
            tmp_moved            = tmp_moved_next;
        }
        if_init = true;
        size    = moved.size;
        // 2. clear the property of `moved` one
        moved.head    = nullptr;
        moved.tail    = nullptr;
        moved.size    = 0;
        moved.if_init = false;
    }
    SingleList(std::initializer_list<T>&& initList) {
        init_head();
        for (const T& element : initList) {
            push_back(element);
        }
    }
    ~SingleList() noexcept { // impossible to throw exception
        for (size_t remained = size; remained > 0; --remained) {
            pop();
        }
        delete_head();
    }

    /// @brief head_node operation

    void init_head() {
        head    = new node();
        if_init = true;
    }
    void delete_head() {
        if (head) {
            delete head;
        }
    }

    /// @brief data_io operation

    T pop() {
        if (tail == nullptr) {
            throw std::out_of_range("There's NO node in this linked list!");
        };
        // locate tail
        node* tmp = head;
        while (tmp->next != tail) {
            tmp = tmp->next;
        } // tmp->next == tail
        node* deleted_tail = tmp->next;
        delete tmp->next;
        tail = tmp;
        --size;
        return deleted_tail->element;
    }
    void push_back(const T& input) {
        if (!if_init) {
            throw std::out_of_range("The linked list hasn't been initialized!");
        }
        node* to_add = new node(input);
        if (tail == nullptr) {
            head->next = to_add;
            tail       = to_add;
        } else {
            tail->next = to_add;
            tail       = to_add;
        }
        ++size;
    }
    void push_front(const T& input) {
        if (!if_init) {
            throw std::out_of_range("The linked list hasn't been initialized!");
        }
        node* to_add = new node(input);
        if (tail == nullptr) {
            head->next = to_add;
            tail       = to_add;
        } else {
            to_add->next = head->next;
            head->next   = to_add;
        }
        ++size;
    }
    void add_back(const T& input) {
        push_back(input);
    }
    void add_front(const T& input) {
        add_front(input);
    }

    /// @brief function

    void echo() {
        std::cout << "range-based loop => ";
        for (const T& element : *this) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        std::cout << "  old-style loop => ";
        node* tmp = head->next;
        while (tmp != nullptr) {
            std::cout << tmp->element << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }
    void std_sort() {
        std::cout << std::endl;
        std::cout << "Single-direction linked list cannot use std::sort()!" << std::endl;
        std::cout << std::endl;
    }
    void reverse() {
        if (size == 0) {
            return; // don't need to!
        }
    }
};

} // namespace DS