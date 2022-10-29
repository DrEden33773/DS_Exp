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
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
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
    Node* TheRoot = nullptr;
    int   size    = 0;

    /// @brief @b Recursive_Order_Template_Functions
    void PreOrderOpt_Rec(Node* node, std::function<void(Node*)>& func) {
        if (!node) {
            return;
        }
        func(node);
        PreOrderOpt_Rec(node->left, func);
        PreOrderOpt_Rec(node->right, func);
    }
    void InOrderOpt_Rec(Node* node, std::function<void(Node*)>& func) {
        if (!node) {
            return;
        }
        InOrderOpt_Rec(node->left, func);
        func(node);
        InOrderOpt_Rec(node->right, func);
    }
    void PostOrderOpt_Rec(Node* node, std::function<void(Node*)>& func) {
        if (!node) {
            return;
        }
        PostOrderOpt_Rec(node->left, func);
        PostOrderOpt_Rec(node->right, func);
        func(node);
    }

    /// @brief @b Iterative_Order_Template_Functions
    void LevelOrderOpt(Node* input, std::function<void(Node*)>& func) {
        Node* node = input; // copy the ptr
                            // Avoid change the direction of `input` ptr

        if (!node) { // uninitialized
            return;
        }
        std::queue<Node*> opt_stack;
        opt_stack.push(node);

        while (!opt_stack.empty()) {
            Node* curr_node = opt_stack.front();
            func(curr_node);
            if (curr_node->left) {
                opt_stack.push(curr_node->left);
            }
            if (curr_node->right) {
                opt_stack.push(curr_node->right);
            }
            opt_stack.pop();
        }
    }
    void PreOrderOpt(Node* input, std::function<void(Node*)>& func) {
        Node* node = input; // copy the ptr
                            // Avoid change the direction of `input` ptr

        if (!node) { // uninitialized
            return;
        }

        std::stack<Node*> opt_stack;
        // condition `node` => specifically designed for `emplace the first node`
        // if only `!opt_stack.empty()`, never try to get into the loop
        while (node || !opt_stack.empty()) {
            while (node) {
                // Opt
                func(node);
                // All left-sub-tree
                opt_stack.push(node);
                node = node->left;
            }
            node = opt_stack.top(); // trace back
            opt_stack.pop();
            // To a right-sub-tree
            node = node->right;
        }
    }
    void InOrderOpt(Node* input, std::function<void(Node*)>& func) {
        Node* node = input; // copy the ptr

        if (!node) { // uninitialized
            return;
        }

        std::stack<Node*> opt_stack;
        // condition `node` => specifically designed for `emplace the first node`
        // if only `!opt_stack.empty()`, never try to get into the loop
        while (node || !opt_stack.empty()) {
            while (node) {
                // All left-sub-tree
                opt_stack.push(node);
                node = node->left;
            }
            // Opt
            node = opt_stack.top(); // trace back
            opt_stack.pop();
            func(node);
            // To a right-sub-tree
            node = node->right;
        }
    }
    void PostOrderOpt(Node* input, std::function<void(Node*)>& func) {
        Node* node = input; // copy the ptr
                            // Avoid change the direction of `input` ptr

        if (!node) { // uninitialized
            return;
        }

        // <node, flag> (flag => 0: finished left, 1: finished left & right)
        std::stack<std::pair<Node*, int>> opt_stack;
        // condition `node` => specifically designed for `emplace the first node`
        // if only `!opt_stack.empty()`, never try to get into the loop
        while (node || !opt_stack.empty()) {
            while (node) {
                // All left-sub-tree
                int flag = 0;
                opt_stack.push(std::make_pair(node, flag));
                node = node->left;
            }

            auto& node_flag_pair = opt_stack.top(); // trace back
            node                 = node_flag_pair.first;
            int& flag            = node_flag_pair.second;

            if (flag == 0) { // To a right-sub-tree
                node = node->right;
                flag = 1;
            } else { // opt
                func(node);
                opt_stack.pop();
                node = nullptr; // escape next `left-sub-tree traverse loop`
                                // but node will still updated by the top() of stack
            }
        }
    }

    std::function<void(Node*)> DeleteNode = [this](Node* toDelete) {
        delete toDelete;
        --size;
    };
    std::function<void(Node*)> PrintNode = [](Node* node) {
        std::cout << node->elem << " ";
    };
    std::function<void(Node*)> PrintlnNode = [](Node* node) {
        std::cout << node->elem << std::endl;
    };

public:
    ~BinaryTree() {
        PostOrderOpt(TheRoot, DeleteNode);
    }
    BinaryTree() {
        // give the definations
    }

    /// @brief @b Traverse
    void PreOrderTraverse() {
        PreOrderOpt(TheRoot, PrintNode);
    }
    void InOrderTraverse() {
        InOrderOpt(TheRoot, PrintNode);
    }
    void PostOrderTraverse() {
        PostOrderOpt(TheRoot, PrintNode);
    }
    void LevelOrderTraverse() {
        LevelOrderOpt(TheRoot, PrintNode);
    }
    void PreOrderTraverse(Node* theRoot) {
        PreOrderOpt(theRoot, PrintNode);
    }
    void InOrderTraverse(Node* theRoot) {
        InOrderOpt(theRoot, PrintNode);
    }
    void PostOrderTraverse(Node* theRoot) {
        PostOrderOpt(theRoot, PrintNode);
    }
    void LevelOrderTraverse(Node* theRoot) {
        LevelOrderOpt(theRoot, PrintNode);
    }

    /// @brief @b size_related
    constexpr bool BiTreeEmpty() {
        return size == 0;
    }
    constexpr int BiTreeSize() {
        return size;
    }

    ///@brief @b depth_related
    int BiTreeDepth(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int left  = BiTreeDepth(node->left);
        int right = BiTreeDepth(node->right);
        int res   = std::max(left, right) + 1;
        return res;
    }
    int BiTreeDepth() {
        if (!size) {
            return 0;
        }
        return BiTreeDepth(TheRoot);
    }

    ///@brief @b Node_Relation_Opt
    constexpr Node* Root() {
        return TheRoot;
    }
    constexpr T& Value(Node* node) {
        if (!node) {
            throw std::runtime_error("Input node is NULL. ");
        }
        return std::ref(node->elem);
    }
    Node* Parent(Node* input) {
        if (!input) {
            throw std::runtime_error("Input node is NULL. ");
        }
        if (input == TheRoot) {
            return nullptr;
        }
        std::stack<Node*> opt_stack;
        Node*             node         = input;
        Node*             res          = nullptr;
        bool              if_stop_iter = false;

        while (node || !opt_stack.empty()) {
            while (node) {
                // Opt
                if (node->right == input || node->left == input) {
                    res          = node;
                    if_stop_iter = true;
                    break;
                }
                // All left-sub-tree
                opt_stack.push(node);
                node = node->left;
            }
            if (if_stop_iter) {
                break;
            }
            node = opt_stack.top(); // trace back
            opt_stack.pop();
            // To a right-sub-tree
            node = node->right;
        }

        return res;
    }
    Node* LeftChild(Node* input) {
        Node* node = input;
        Node* res  = nullptr;
        while (node) {
            res  = node->left;
            node = node->left;
        }
        return node;
    }
    Node* RightChild(Node* input) {
        Node* node = input;
        Node* res  = nullptr;
        while (node) {
            res  = node->right;
            node = node->right;
        }
        return node;
    }
    Node* LeftBrother(Node* input) {
        Node* res    = nullptr;
        Node* father = Parent(input);
        if (father) {
            res = (father->left == input) ? nullptr : father->left;
        }
        return res;
    }
    Node* RightBrother(Node* input) {
        Node* res    = nullptr;
        Node* father = Parent(input);
        if (father) {
            res = (father->right == input) ? nullptr : father->right;
        }
        return res;
    }

    /// @brief @b Processing
    void Assign(Node* node, const T& value) {
        if (!node) {
            throw std::runtime_error("Input node is NULL. ");
        }
        node->elem = value;
    }
    void InsertChild(Node* node, Node* toInsert, int LR = 0) {
        if (LR != 0 && LR != 1) {
            throw std::runtime_error("Unknown insert position type. ");
        }
    }
};

} // namespace DS