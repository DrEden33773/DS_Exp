/**
 * @file BinaryTree.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief BinaryTree
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <functional>
#include <iostream>
#include <utility>

namespace DS {

template <typename T>
class BinaryTree {
    struct Node {
        T     elem;
        Node* left  = nullptr;
        Node* right = nullptr;

        Node() = default;
        constexpr explicit Node(const T& elem)
            : elem(elem) { }
    };
    Node* Root = nullptr;

    /// @brief @b Template_Function_Of_Three_Order_Options
    void PreOrderOpt(Node* node, std::function<void(Node*)>& func) {
        if (!node) {
            return;
        }
        func(node);
        PreOrderOpt(node->left, func);
        PreOrderOpt(node->right, func);
    }
    void InOrderOpt(Node* node, std::function<void(Node*)>& func) {
        if (!node) {
            return;
        }
        InOrderOpt(node->left, func);
        func(node);
        InOrderOpt(node->right, func);
    }
    void PostOrderOpt(Node* node, std::function<void(Node*)>& func) {
        if (!node) {
            return;
        }
        PostOrderOpt(node->left, func);
        PostOrderOpt(node->right, func);
        func(node);
    }

    std::function<void(Node*)> DeleteNode = [](Node* toDelete) {
        delete toDelete;
    };
    std::function<void(Node*)> PrintNode = [](Node* node) {
        std::cout << node->elem << " ";
    };
    std::function<void(Node*)> PrintlnNode = [](Node* node) {
        std::cout << node->elem << std::endl;
    };

public:
    ~BinaryTree() {
        PostOrderOpt(Root, DeleteNode);
    }
    BinaryTree() = default;

    /// @brief @b Traverse
    void PreOrderTraverse(Node* theRoot) {
        PreOrderOpt(theRoot, PrintNode);
    }
    void InOrderTraverse(Node* theRoot) {
        InOrderOpt(theRoot, PrintNode);
    }
    void PostOrderTraverse(Node* theRoot) {
        PostOrderOpt(theRoot, PrintNode);
    }
    void PreOrderTraverse() {
        PreOrderOpt(Root, PrintNode);
    }
    void InOrderTraverse() {
        InOrderOpt(Root, PrintNode);
    }
    void PostOrderTraverse() {
        PostOrderOpt(Root, PrintNode);
    }
};

} // namespace DS