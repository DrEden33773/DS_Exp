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
            @e Default_Container @p <equals_to> @b double_list
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

template <typename T>
class ListStack {
private:
    DS::DoubleList<T>* data = nullptr;

public:
    ListStack() {
        data = new DS::DoubleList<T>();
    }
    ListStack(std::initializer_list<T>&& initList) {
        for (auto&& elem : initList) {
            data->push_back(initList);
        }
    }
};

template <typename T>
class VecStack {
private:
    DS::DynamicArray<T>* data = new DS::DynamicArray<T>();
    // base and top
    T* base = data->begin().ptr;
    T* top  = data->end().ptr;

public:
    VecStack() {
    }
    constexpr void update_base_and_top() {
        base = data->begin().ptr;
        top  = data->end().ptr;
    }
    VecStack(std::initializer_list<T>&& initList) {
        for (auto&& elem : initList) {
            data->push_back(elem);
        }
    }
};

template <typename T>
using Stack = VecStack<T>;

} // namespace DS