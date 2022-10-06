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
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <unordered_map>

namespace DS {

template <typename T = int> // default type = int
class DoubleList {
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

    /// @brief @b bidirectional_iterator
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
    /// @brief return the iterator wrapped with `head->next` (first data)
    iterator begin() {
        return iterator(head->next);
    }
    /// @brief return the iterator wrapped with `tail->next` (nullptr)
    iterator end() {
        return iterator(tail->next);
    }
    /// @b each options related to iterator will be in @b [begin(),end()) range

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
};

} // namespace DS