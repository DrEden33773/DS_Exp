/**
 * @file BasicCircleList.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Provides the @e basic_function of a @b Circle_Double_Directed_List
 * @version 0.1
 * @date 2022-10-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>

namespace DS {

template <typename T>
class BasicCircleList {
protected:
    struct node {
        T     element;
        node* next = nullptr;
        node* prev = nullptr;
        node()     = default;
        constexpr explicit node(const T& element)
            : element(element) { }
    };
    node* head     = nullptr; // head node maintain data
    node* tail     = nullptr; // tail node maintain data
    int   size     = 0;
    bool  if_moved = false;

    /// @brief @b bidirectional_iterator
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        node* ptr = nullptr;

        constexpr explicit iterator(node* ptr)
            : ptr(ptr) { }

        iterator operator++() {
            ptr = ptr->next;
            return *this;
        }
        iterator operator--() {
            ptr = ptr->prev;
            return *this;
        }
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
        iterator operator+(int distance) {
            iterator res = *this;
            if (distance > 0) {
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->next;
                }
            } else if (distance < 0) { // change to the abs value
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->prev;
                }
            }
            return res;
        }
        iterator operator-(int distance) {
            iterator res = *this;
            if (distance > 0) {
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->prev;
                }
            } else if (distance < 0) { // change to the abs value
                distance *= -1;
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->next;
                }
            }
            return res;
        }
        iterator operator+=(int n) {
            iterator tmp = (*this) + n;
            this->ptr    = tmp.ptr;
            return *this;
        }
        iterator operator-=(int n) {
            iterator tmp = (*this) - n;
            this->ptr    = tmp.ptr;
            return *this;
        }

        int operator-(const iterator& rhs) {
            // assume that `rhs` -> ... -> `this` (will be verified later)
            int   distance           = 0;
            node* this_ptr           = this->ptr;
            node* rhs_ptr            = rhs.ptr;
            node* original_rhs_ptr   = rhs.ptr;
            bool  if_rhs_behind_this = false;
            while (rhs_ptr != nullptr) {
                if (rhs_ptr == this->ptr) {
                    break;
                }
                rhs_ptr = rhs_ptr->next;
                ++distance;
            } // maybe rhs.ptr == nullptr
            if (rhs_ptr == nullptr) {
                if_rhs_behind_this = true;
            }
            if (if_rhs_behind_this) {
                rhs_ptr  = original_rhs_ptr;
                distance = 0;
                // now `this` -> ... -> `rhs`
                while (this_ptr != nullptr) {
                    if (this_ptr == rhs_ptr) {
                        break;
                    }
                    this_ptr = this_ptr->next;
                    ++distance;
                }
            }
            return distance;
        }

        T&   operator*() const { return ptr->element; }
        T*   operator->() const { return &(ptr->element); }
        bool operator!=(const iterator& rhs) const { return ptr != rhs.ptr; }
        bool operator==(const iterator& rhs) const { return ptr == rhs.ptr; }
        bool operator>(const iterator& rhs) const {
            return BasicCircleList::if_A_behind_B(this->ptr, rhs.ptr);
        }
        bool operator>=(const iterator& rhs) const {
            bool behind = BasicCircleList::if_A_behind_B(this->ptr, rhs.ptr);
            bool eq     = BasicCircleList::if_A_is_B(this->ptr, rhs.ptr);
            return behind || eq;
        }
        bool operator<(const iterator& rhs) const {
            return BasicCircleList::if_A_ahead_B(this->ptr, rhs.ptr);
        }
        bool operator<=(const iterator& rhs) const {
            bool ahead = BasicCircleList::if_A_ahead_B(this->ptr, rhs.ptr);
            bool eq    = BasicCircleList::if_A_is_B(this->ptr, rhs.ptr);
            return ahead || eq;
        }
    };
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(tail->next);
    }
    /// @b each operation related to iterator will be in @b [begin(),end()) range

    /// @brief relative location relation resolver
    static bool if_A_ahead_B(node* A, node* B) { // A -> ... -> B
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
    static bool if_A_behind_B(node* A, node* B) { // B -> ... -> A
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
    static constexpr bool if_A_is_B(node* A, node* B) { // B == A
        return A == B;
    }
    static constexpr bool if_A_is_not_B(node* A, node* B) { // B != A
        return A != B;
    }

    /// @brief static constructor
    static BasicCircleList<T>&& CreateDoubleList(
        std::initializer_list<T>&& initList
    ) {
        using original_type = std::initializer_list<T>;
        BasicCircleList<T> created(std::forward<original_type>(initList));
        created.if_moved = true;
        return std::move(created);
    }

    /// @brief constexpr operation
    constexpr bool if_empty() noexcept {
        return this->size == 0;
    }
    constexpr int get_length() noexcept {
        return this->size;
    }
    constexpr int get_size() noexcept {
        return this->size;
    }

    /// @brief object management
    BasicCircleList()                                 = default; // default constructor
    BasicCircleList(BasicCircleList&& moved) noexcept = default; // move constructor
    BasicCircleList(const BasicCircleList& copied) {             // copy constructor
        for (const T& element : copied) {
            push_back(element);
        }
    }
    BasicCircleList(std::initializer_list<T>&& initList) {
        for (const T& element : initList) {
            push_back(element);
        }
    }
    ~BasicCircleList() noexcept { // impossible to throw exception
        if (if_moved) {
            return;
        }
        while (tail != head) { // do not rely on size, will be better!
            pop_back();
        }
        delete head; // delete tail;
    }

    /// @brief data_io operation
    T pop_back() { // remove `tail`
        if (tail == nullptr) {
            throw std::out_of_range("There's NO node in this linked list!");
        }
        node* new_tail  = tail->prev;
        node* old_tail  = tail;
        T     to_return = old_tail->element;
        new_tail->next  = nullptr;
        delete tail;
        tail = new_tail;
        --size;
        return to_return;
    }
    T pop_front() { // remove `head->next`
        if (tail == nullptr) {
            throw std::out_of_range("There's NO node in this linked list!");
        }
        T returned_elem;
        if (size == 1) {
            returned_elem = head->element;
            delete head;
            --size;
        } else {
            node* deleted       = head->next;
            node* new_head_next = deleted->next;
            returned_elem       = deleted->element;
            head->next          = new_head_next;
            new_head_next->prev = head;
            delete deleted;
            --size;
            if (size == 1) {
                tail = head;
            }
        }
        return returned_elem;
    }
    void push_back(const T& input) {
        node* to_add = new node(input);
        if (tail == nullptr) {
            head->next = to_add;
            tail       = to_add;
            tail->prev = head;
        } else {
            tail->next   = to_add;
            to_add->prev = tail;
            tail         = to_add;
        }
        ++size;
    }
    void push_front(const T& input) {
        node* to_add = new node(input);
        if (tail == nullptr) {
            head->next = to_add;
            tail       = to_add;
            tail->prev = head;
        } else {
            node* the_next = head->next;
            to_add->next   = the_next;
            if (the_next != nullptr) { // or, the_next == nullptr
                the_next->prev = to_add;
            }
            to_add->prev = head;
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
    }
};

} // namespace DS