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

namespace DS {

template <typename T = int> // default type = int
class SingleList {
private:
    struct node {
        T     element;
        node* next = nullptr;
        explicit node(T& element) { this->element = element; }
    };
    node*  head     = nullptr; // head is always a nullptr
    node*  tail     = nullptr;
    size_t node_num = 0;

public:
};

} // namespace DS