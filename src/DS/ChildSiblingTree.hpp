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

public:
    void make_sure_exist(const T& in) {
        if (!Members.contains(in)) {
            throw std::logic_error("Input member doesn't exist on the full list!");
        }
    }
    void make_sure_non_statistic(const T& in) {
        if (CountedMembers.contains(in)) {
            throw std::logic_error("Input member is statistic(on the tree)!");
        }
    }
    void make_sure_statistic(const T& in) {
        if (!CountedMembers.contains(in)) {
            throw std::logic_error("Input member is statistic(on the tree)!");
        }
    }
    void make_sure_have_ancestor() {
        if (!Ancestor) {
            throw std::logic_error("There's no ancestor! You should `set_ancestor()` first!");
        }
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
        ++size;
    }
    void set_child_of(
        const T&              parent,
        const std::vector<T>& children
    ) {
        if (children.empty()) {
            return;
        }

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
            ++size;
        }
    }
};

} // namespace DS