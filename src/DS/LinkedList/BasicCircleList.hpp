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
};

} // namespace DS