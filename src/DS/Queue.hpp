/**
 * @file Queue.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
        An implementation of Stack.

        The Container should satisfy the `LIFO` standard interface,
        and has at least @b queue_base{type->ptr} and @b queue_top{type->ptr}.
 *
 * @attention
        @b Queue is a @e container_adapter , which is an @b encapsulation_of_container
            (which satisfy @b rear_push_and_front_pop operation)
            { @e example=> @b DynamicArray , @b SingleList , @b DoubleList(List) ... }

        Take @b S(n) and @b T(n) into consideration, the final implementation is:
            @e Default_Container @p <equals_to> @b double_list(list)
            @e Supported_Container @p <equals_to> @b DoubleList__&__DynamicArray
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "LinkedList/DoubleList.hpp"
#include "List.hpp"
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>

namespace DS {

/// @brief @b Chained_Queue
template <typename T>
class ChainedQueue {
    using node     = typename DS::List<T>::node;
    using iterator = typename DS::List<T>::iterator;

    /// @brief @b data_front_rear
    DS::List<T>* data  = new DS::List<T>();
    node*        front = data->head;
    node*        rear  = data->tail;

    /// @brief @b iterator_opt
    iterator begin() {
        return data->begin();
    }
    iterator end() {
        return data->end();
    }

    /// @brief @b update_front_and_rear
    constexpr void update_front_and_rear() {
        front = data->head;
        rear  = data->tail;
    }

public:
    ChainedQueue() = default;
    ~ChainedQueue() {
        delete data;
        front = nullptr;
        rear  = nullptr;
    }
    ChainedQueue(ChainedQueue<T>&& moved) noexcept
        : data(moved.data)
        , front(moved.front)
        , rear(moved.rear) {
        moved.base  = nullptr;
        moved.front = nullptr;
        moved.rear  = nullptr;
    }
    ChainedQueue(ChainedQueue<T>& copied)
        : data(new DS::List<T>(copied.data)) {
        update_front_and_rear();
    }
    ChainedQueue(std::initializer_list<T>&& initList) {
        for (auto&& elem : initList) {
            data->push_back(elem);
        }
        update_front_and_rear();
    }

    void push_back(const T& elem) {
        data->push_back(elem);
        update_front_and_rear();
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
    T pop_front() {
        T front_elem = data->pop_front();
        update_front_and_rear();
        return front_elem;
    }
    T pop() {
        return pop_front();
    }
    T get_front() {
        return data->get_elem(1);
    }
    T get() {
        return get_front();
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
using Queue = ChainedQueue<T>;

} // namespace DS