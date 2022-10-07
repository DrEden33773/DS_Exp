/**
 * @file DoubleList.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Linked list with two directions
 * @structure:
        head<->[data|ptr]<->[data|ptr]<->...<->[data|ptr]-> nullptr
                                            ^^^^------> tail
 * @version 0.1
 * @date 2022-10-06
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
#include <unordered_map>

namespace DS {

template <typename T = int> // default type = int
struct DoubleList {         // all public, for algorithm
    static const std::string DSname;

    struct node {
        T     element;
        node* next = nullptr;
        node* prev = nullptr;
        node()     = default;
        explicit node(const T& element) { this->element = element; }
    };
    node* head    = nullptr; // head node never maintain data
    node* tail    = nullptr; // tail node always maintain data
    bool  if_init = false;   // if init head node
    int   size    = 0;       // num of nodes (except head node)
                             // (num of effective nodes)
    bool if_moved = false;   // if temporarily created object will be moved
                             // if so, deleter won't be called

    /// @brief @b return_name
    virtual const char* return_name() final {
        return "Double-List";
    }

    /// @brief @b bidirectional_iterator
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        node* ptr = nullptr;

        explicit iterator(node* ptr) { this->ptr = ptr; }

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
            return DoubleList::if_A_behind_B(this->ptr, rhs.ptr);
        }
        bool operator>=(const iterator& rhs) const {
            bool behind = DoubleList::if_A_behind_B(this->ptr, rhs.ptr);
            bool eq     = DoubleList::if_A_is_B(this->ptr, rhs.ptr);
            return behind || eq;
        }
        bool operator<(const iterator& rhs) const {
            return DoubleList::if_A_ahead_B(this->ptr, rhs.ptr);
        }
        bool operator<=(const iterator& rhs) const {
            bool ahead = DoubleList::if_A_ahead_B(this->ptr, rhs.ptr);
            bool eq    = DoubleList::if_A_is_B(this->ptr, rhs.ptr);
            return ahead || eq;
        }
    };
    iterator begin() {
        return iterator(head->next);
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

public:
    /// @brief static constructor
    static DoubleList<T>&& CreateDoubleList(
        std::initializer_list<T>&& initList
    ) {
        using original_type = std::initializer_list<T>;
        DoubleList<T> created(std::forward<original_type>(initList));
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
    DoubleList() { // default constructor (not recommended!)
        init_head();
    }
    DoubleList(const DoubleList& copied) { // copy constructor
        init_head();
    }
    DoubleList(DoubleList&& moved) noexcept { // move constructor

        // 1. guarantee `this`
        if_init = true;
        size    = moved.size;
        // (1) => locate head and tail
        head = moved.head;
        tail = moved.tail;
        // (2) => locate each node of `this` && set null to each node of `moved`
        node* curr      = head;
        node* tmp_moved = moved.head;
        while (tmp_moved != nullptr) {
            // link node in `this` with moved
            curr       = tmp_moved;
            curr->next = tmp_moved->next;
            curr->prev = tmp_moved->prev;
            curr       = curr->next;
            // free moved
            node* tmp_moved_next = tmp_moved->next;
            tmp_moved            = nullptr;
            tmp_moved            = tmp_moved_next;
        }
        // 2. clear the property of `moved` one
        moved.head    = nullptr;
        moved.tail    = nullptr;
        moved.size    = 0;
        moved.if_init = false;
    }
    DoubleList(std::initializer_list<T>&& initList) {
        init_head();
        for (const T& element : initList) {
            push_back(element);
        }
    }
    ~DoubleList() noexcept { // impossible to throw exception
        if (if_moved) {
            return;
        }
        for (size_t remained = size; remained > 0; --remained) {
            pop_back();
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
    T pop_back() { // remove `tail`
        if (tail == nullptr) {
            throw std::out_of_range("There's NO node in this linked list!");
        }
        node* new_tail = tail->prev;
        node* old_tail = tail;
        new_tail->next = nullptr;
        delete tail;
        tail = new_tail;
        --size;
        return old_tail->element;
    }
    T pop_front() { // remove `head->next`
        if (tail == nullptr) {
            throw std::out_of_range("There's NO node in this linked list!");
        }
        node* deleted       = head->next;
        node* new_head_next = deleted->next;
        T     returned_elem = deleted->element;
        head->next          = new_head_next;
        new_head_next->prev = head;
        delete deleted;
        --size;
        return returned_elem;
    }
    void push_back(const T& input) {
        if (!if_init) {
            throw std::out_of_range("The linked list hasn't been initialized!");
        }
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
        if (!if_init) {
            throw std::out_of_range("The linked list hasn't been initialized!");
        }
        node* to_add = new node(input);
        if (tail == nullptr) {
            head->next = to_add;
            tail       = to_add;
            tail->prev = head;
        } else {
            node* the_next = head->next;
            to_add->next   = the_next;
            the_next->prev = to_add;
            to_add->prev   = head;
            head->next     = to_add;
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
        for (const T& element : *this) { // this will use the iterator
            std::cout << element << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
        // std::cout << "  old-style loop => ";
        // node* tmp = head->next;
        // while (tmp != nullptr) {
        //     std::cout << tmp->element << " ";
        //     tmp = tmp->next;
        // }
        // std::cout << std::endl;
    }
    void std_sort() {
        if (head->next == nullptr) {
            std::cout << return_name() << " is empty, will escape sorting. " << std::endl;
            std::cout << std::endl;
        }
        std::sort(begin(), end());
        std::cout << return_name() << " called std::sort()" << std::endl;
        std::cout << std::endl;
    }
};

template <typename T>
const std::string DoubleList<T>::DSname = "DoubleList";

} // namespace DS