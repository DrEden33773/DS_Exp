/**
 * @file Stack.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
        An implementation of Stack.

        The Container should satisfy the `LIFO` standard interface,
        and has at least @b stack_base{type->ptr} and @b stack_top{type->ptr}.
 *
 * @attention
        @b Stack is a @e container_adapter , which is an @b encapsulation_of_container
            (which satisfy @b tail_push_and_pop operation)
            { @e example=> @b DynamicArray , @b SingleList , @b DoubleList ... }

        Take @b S(n) and @b T(n) into consideration, the final implementation is:
            @e Default_Container @p <equals_to> @b dynamic_array
            @e Supported_Container @p <equals_to> @b DoubleList__&__DynamicArray
 * @version 0.1
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "DynamicArray.hpp"
#include "LinkedList/DoubleList.hpp"
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace DS {

/// @brief @b Sequential_Stack
template <typename T>
class SeqStack {
    using iterator = typename DynamicArray<T>::iterator;

    /// @brief @b data_base_top
    DS::DynamicArray<T>* data = new DS::DynamicArray<T>();
    T*                   base = data->begin().ptr;
    T*                   top  = data->end().ptr;

    /// @brief @b iterator_opt
    iterator begin() {
        return data->begin();
    }
    iterator end() {
        return data->end();
    }

    /// @brief @b update_base_and_top
    constexpr void update_base_and_top() {
        base = data->begin().ptr;
        top  = data->end().ptr;
    }

public:
    SeqStack()
        : data(new DS::DynamicArray<T>) {
        update_base_and_top();
    }
    ~SeqStack() {
        delete data;
        top  = nullptr;
        base = nullptr;
    }
    SeqStack& operator=(const SeqStack& copied) {
        if (&copied == this) {
            return *this;
        }
        data = new DS::DynamicArray<T>(copied.data);
        update_base_and_top();
        return *this;
    }
    SeqStack& operator=(SeqStack&& moved) noexcept {
        data       = moved.data;
        base       = moved.base;
        top        = moved.top;
        moved.base = nullptr;
        moved.top  = nullptr;
        moved.data = nullptr;
        return *this;
    }
    SeqStack(const SeqStack<T>& copied)
        : data(new DS::DynamicArray<T>(copied.data)) {
        update_base_and_top();
    }
    SeqStack(SeqStack<T>&& moved) noexcept
        : data(moved.data)
        , base(moved.base)
        , top(moved.top) {
        moved.base = nullptr;
        moved.top  = nullptr;
        moved.data = nullptr;
    }
    SeqStack(const std::initializer_list<T>& initList) {
        for (auto&& elem : initList) {
            data->push_back(elem);
        }
        update_base_and_top();
    }
    explicit SeqStack(const std::vector<T>& initList) {
        for (auto&& elem : initList) {
            data->push_back(elem);
        }
        update_base_and_top();
    }

    void push_back(const T& elem) {
        data->push_back(elem);
        update_base_and_top();
    }
    void push(const T& elem) {
        push_back(elem);
    }
    template <typename... Args>
    void push_back(const T& single, const Args&... input) {
        push_back(single);
        if constexpr (sizeof...(input) > 0) {
            push_back(input...);
        }
    }
    template <typename... Args>
    void push(const T& single, const Args&... input) {
        push_back(single);
        if constexpr (sizeof...(input) > 0) {
            push_back(input...);
        }
    }
    T pop_back() {
        T top_elem = data->pop_back();
        update_base_and_top();
        return top_elem;
    }
    T pop() {
        return pop_back();
    }
    T get_back() {
        return data->get_back();
    }
    T get() {
        return get_back();
    }
    bool if_empty() {
        return data->if_empty();
    }
    int get_length() {
        return data->get_length();
    }

    void echo() {
        data->echo();
    }
};

template <typename T>
using Stack = SeqStack<T>;

} // namespace DS