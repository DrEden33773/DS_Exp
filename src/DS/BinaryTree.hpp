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
    struct node {
        T     elem;
        node* left  = nullptr;
        node* right = nullptr;
    };
    node* Root = nullptr;

    /// @brief @b Template_Function_Of_Three_Order_Options
    void PreOrderOpt(node* toOpt, std::function<void(node* toOpt)>& func) {
        if (!toOpt) {
            return;
        }
        func(toOpt);
        PreOrderOpt(toOpt->left, func);
        PreOrderOpt(toOpt->right, func);
    }
    void InOrderOpt(node* toOpt, std::function<void(node* toOpt)>& func) {
        if (!toOpt) {
            return;
        }
        InOrderOpt(toOpt->left, func);
        func(toOpt);
        InOrderOpt(toOpt->right, func);
    }
    void PostOrderOpt(node* toOpt, std::function<void(node* toOpt)>& func) {
        if (!toOpt) {
            return;
        }
        PostOrderOpt(toOpt->left, func);
        PostOrderOpt(toOpt->right, func);
        func(toOpt);
    }

public:
    void DeleteNode(node* toDelete) {
        delete toDelete;
    }
    ~BinaryTree() {
        PostOrderOpt(Root, DeleteNode(Root));
    }

    void PrintNode(node* toPrint) {
        std::cout << toPrint->elem << " ";
    }
    void PrintlnNode(node* toPrint) {
        std::cout << toPrint->elem << std::endl;
    }

    void PreOrderTraverse(node* theRoot) {
        PreOrderOpt(theRoot, PrintNode(theRoot));
    }
    void InOrderTraverse(node* theRoot) {
        InOrderOpt(theRoot, PrintNode(theRoot));
    }
    void PostOrderTraverse(node* theRoot) {
        PostOrderOpt(theRoot, PrintNode(theRoot));
    }
};

} // namespace DS