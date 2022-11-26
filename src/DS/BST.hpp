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
    Node* TheRoot  = nullptr;
    int   size     = 0;
    using NodePair = std::pair<Node*, Node*>;

private:
    /* < max_node, parent_node > */
    NodePair find_max_and_parent(Node* input, Node* parent) {
        NodePair ret = std::make_pair(nullptr, nullptr);
        while (input->right) {
            parent = input;
            input  = input->right;
        }
        ret.first  = input;
        ret.second = parent;
        return ret;
    }
    /* < min_node, parent_node > */
    NodePair find_min_and_parent(Node* input, Node* parent) {
        NodePair ret = std::make_pair(nullptr, nullptr);
        while (input->left) {
            parent = input;
            input  = input->left;
        }
        ret.first  = input;
        ret.second = parent;
        return ret;
    }

    void delete_tree(Node* toDelete) {
        if (toDelete) {
            delete_tree(toDelete->left);
            delete_tree(toDelete->right);
            delete toDelete;
            --size;
        }
    }
    void delete_all_node() {
        delete_tree(TheRoot);
    }

private:
    void remove_leaf(Node*& toRemove, Node*& parent) {
        // de-link
        if (parent->left == toRemove) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        // remove
        delete toRemove;
        --size;
    }
    void remove_single_branch(Node*& toRemove, Node*& parent) {
        // de-link
        bool if_removed_left = false;
        if (parent->left == toRemove) {
            parent->left    = nullptr;
            if_removed_left = true;
        } else {
            parent->right = nullptr;
        }
        // judge
        bool if_left_branch = toRemove->left != nullptr;
        // re-link
        if (if_left_branch) {
            if (if_removed_left) {
                parent->left = toRemove->left;
            } else {
                parent->right = toRemove->left;
            }
        } else {
            if (if_removed_left) {
                parent->left = toRemove->right;
            } else {
                parent->right = toRemove->right;
            }
        }
        // delete
        delete toRemove;
        --size;
    }
    void remove_double_branch(Node*& toRemove, Node*& parent) {
        NodePair received = find_max_and_parent(
            toRemove->left,
            toRemove
        );
        // get => max_of_left_sub_tree & it's parent
        Node* left_max           = received.first;
        Node* parent_of_left_max = received.second;
        // de-link left-max & re-link left-max's left sub tree
        if (parent_of_left_max != toRemove) {
            parent_of_left_max->right = left_max->left;
            /* left_max->right == nullptr */
        } else {
            parent_of_left_max->left = left_max->left;
            /* left_max->right == nullptr */
        }
        // toRemove->elem <== left_max->elem [use std::move()]
        toRemove->elem = std::move(left_max->elem);
        // left_max's elem has been moved, delete the node
        delete left_max;
        --size;
    }
    void remove_node(Node*& toRemove, Node*& parent) {
        if (toRemove->left && toRemove->right) {
            remove_double_branch(toRemove, parent);
        } else if (!toRemove->left && !toRemove->right) {
            remove_leaf(toRemove, parent);
        } else {
            remove_single_branch(toRemove, parent);
        }
    }

public:
    ~BST() {
        delete_all_node();
    }
    void insert(const T& val) {
        Node* toInsert = new Node(val);
        if (!TheRoot) {
            TheRoot = toInsert;
            ++size;
            return;
        }
        Node* parent  = nullptr;
        Node* current = TheRoot;
        while (current) {
            if (val < current->elem) {
                parent  = current;
                current = current->left;
            } else if (val > current->elem) {
                parent  = current;
                current = current->right;
            } else {
                return;
            }
        }
        if (val < parent->elem) {
            parent->left = toInsert;
        } else {
            parent->right = toInsert;
        }
        ++size;
    }
    void remove(const T& val) {
        Node* node = TheRoot;
        if (!node) {
            return;
        }
        Node* parent  = nullptr;
        Node* current = TheRoot;
        while (current) {
            if (val < current->elem) {
                parent  = current;
                current = current->left;
            } else if (val > current->elem) {
                parent  = current;
                current = current->right;
            } else {
                break;
            }
        }
        remove_node(current, parent);
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