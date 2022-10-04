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
    node*  head    = nullptr; // head node never maintain data
    node*  tail    = nullptr; // tail node always maintain data
    bool   if_init = false;   // if init head node
    size_t size    = 0;       // size of nodes (except head node)
                              // (size of effective nodes)

    class iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        node* ptr = nullptr;
        explicit iterator(node* ptr) { this->ptr = ptr; }
        iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        T&   operator*() { return ptr->element; }
        T*   operator->() { return &(ptr->element); }
        bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; }
        // bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
    };
    iterator begin() {
        return iterator(head->next);
    }
    iterator end() {
        return iterator(tail->next);
    }

public:
    SingleList() { // default constructor (not recommended!)
        init_head();
    }
    SingleList(const SingleList& copied) { // copy constructor
        init_head();
    }
    SingleList(SingleList&& moved) noexcept { // move constructor
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

    void init_head() {
        head    = new node();
        if_init = true;
    }
    void delete_head() {
        if (head) {
            delete head;
        }
    }

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
};

} // namespace DS