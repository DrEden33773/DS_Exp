/**
 * @file BST.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <concepts>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace DS {

template <typename T>
requires std::equality_comparable<T>
class BST {
    struct Node {
        T     elem;
        Node* left  = nullptr;
        Node* right = nullptr;

        Node() = default;
        constexpr explicit Node(const T& elem)
            : elem(elem) { }
    };
    Node* TheRoot = nullptr;
    int   size    = 0;

public:
    void insert(const T& val) {
    }
    void remove(const T& val) {
    }
    void print_tree() {
        Node* node = TheRoot;
        if (!node) {
            return;
        }
        std::stack<Node*> stack;
        while (node || !stack.empty()) {
            while (node) {
                // All left-sub-tree
                stack.push(node);
                node = node->left;
            }
            // print
            node = stack.top(); // trace back
            stack.pop();
            std::cout << node->elem << " ";
            // To a right-sub-tree
            node = node->right;
        }
        std::cout << std::endl;
    }
};

} // namespace DS