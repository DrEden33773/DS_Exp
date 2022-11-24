/**
 * @file ChildSiblingTree.hpp
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
#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace DS {

template <typename T>
class ChildSiblingTree {
    struct Node {
        T     elem;
        Node* child   = nullptr;
        Node* sibling = nullptr;

        Node() = default;
        constexpr explicit Node(const T& elem)
            : elem(elem) { }
    };
    Node* Ancestor = nullptr;
    int   size     = 0;

    std::unordered_set<T>        Members;        // all members info
    std::unordered_set<T>        CountedMembers; // those who's on the tree
    std::unordered_map<T, Node*> MemberPtrMap;   // Member -> Ptr

public:
    explicit ChildSiblingTree(const std::vector<T>& init)
        : size(init.size()) {
        for (auto&& curr_member : init) {
            Members.insert(curr_member);
        }
    }
    void make_sure_exist(const T& in) {
        if (!Members.contains(in)) {
            throw std::logic_error("Input member doesn't exist! Consider `add_member()` first!");
        }
    }
    void make_sure_non_statistic(const T& in) {
        if (CountedMembers.contains(in)) {
            throw std::logic_error("Input member isn't on the tree!");
        }
    }
    void make_sure_statistic(const T& in) {
        if (!CountedMembers.contains(in)) {
            throw std::logic_error("Input member is already on the tree!");
        }
    }
    void make_sure_have_ancestor() {
        if (!Ancestor) {
            throw std::logic_error("There's no ancestor! You should `set_ancestor()` first!");
        }
    }

public:
    void add_member(const T& toAdd) {
        Members.insert(toAdd);
    }
    void set_ancestor(const T& in) {
        make_sure_exist(in);
        make_sure_non_statistic(in);

        Node* the_ancestor = new Node(in);
        Ancestor           = the_ancestor;

        CountedMembers.insert(in);
        MemberPtrMap.insert(
            std::make_pair(in, Ancestor)
        );
    }
    void set_child_of(
        const T&              parent,
        const std::vector<T>& children
    ) {
        make_sure_have_ancestor();

        make_sure_exist(parent);
        make_sure_statistic(parent); // parent should on the tree
        for (auto&& child : children) {
            make_sure_exist(child);
            make_sure_non_statistic(child); // children shouldn't on the tree
        }

        Node* ParentPtr       = MemberPtrMap.at(parent);
        int   index           = 0;
        Node* closest_sibling = nullptr;

        for (auto&& child : children) {
            if (!index) {
                // first child
                Node* firstChild = new Node(child);
                ParentPtr->child = firstChild;
                CountedMembers.insert(child);
                MemberPtrMap.insert(std::make_pair(child, firstChild));
                closest_sibling = firstChild;
            } else {
                // sibling
                Node* new_sibling        = new Node(child);
                closest_sibling->sibling = new_sibling;
                CountedMembers.insert(child);
                MemberPtrMap.insert(std::make_pair(child, new_sibling));
                closest_sibling = new_sibling;
            }
            ++index;
        }
    }
    void debug_print_tree() {
        if (!Ancestor) {
            std::cout << "Tree is empty!" << std::endl;
            std::cout << std::endl;
            return;
        }
        Node*             node = Ancestor;
        std::stack<Node*> stack;
        int               indentation = 0;
        while (!stack.empty() || node) {
            while (node) {
                // print
                int curr_indentation = indentation;
                while (curr_indentation-- > 0) {
                    std::cout << "  ";
                }
                std::cout << node->elem << std::endl;
                // notation
                stack.push(node);
                // move to child
                node = node->child;
                // add indentation
                ++indentation;
            }
            // trace back
            node = stack.top();
            stack.pop();
            --indentation;
            // move to sibling
            node = node->sibling;
        }
        std::cout << std::endl;
    }
    void print_layer(const size_t& layer) {
        if (layer < 1) {
            throw std::logic_error("Layer must >= 1 !");
        }
        // BFS
        if (!Ancestor) {
            return;
        }
        Node*             node = Ancestor;
        std::queue<Node*> queue;
        queue.push(Ancestor);
        size_t curr_layer = 1;
        while (!queue.empty()) {
            size_t curr_layer_size = queue.size();
            while (curr_layer_size-- > 0) {
                node = queue.front();
                if (curr_layer == layer) {
                    std::cout << node->elem << " ";
                }
                queue.pop();
                if (node->child) {
                    queue.push(node->child);
                    Node* closest_sibling = node->child->sibling;
                    while (closest_sibling) {
                        queue.push(closest_sibling);
                        closest_sibling = closest_sibling->sibling;
                    }
                }
            }
            if (curr_layer == layer) {
                break;
            }
            ++curr_layer;
        }
        std::cout << std::endl;
    }
};

} // namespace DS