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
#include <type_traits>
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

    /// @brief @b default_constructor
    BinaryTree() = default;

public:
    enum class Order : unsigned short {
        LevelOrder = 0,
        PreOrder   = 1,
        InOrder    = 2,
        PostOrder  = 3,
    };

    /// @brief @b destructor
    ~BinaryTree() {
        PostOrderOpt(TheRoot, DeleteNode);
    }

    /// @brief @b move_constructor_and_assigner
    BinaryTree(BinaryTree&& moved) noexcept
        : size(moved.size)
        , TheRoot(moved.TheRoot) {
        moved.size    = 0;
        moved.TheRoot = nullptr;
    }
    BinaryTree& operator=(BinaryTree&& moved) noexcept {
        size          = moved.size;
        TheRoot       = moved.TheRoot;
        moved.size    = 0;
        moved.TheRoot = nullptr;
        return *this;
    }

    /// @brief @b copy_constructor_and_assigner
    BinaryTree(const BinaryTree& copied) {
        // TODO(eden): Deserialize and then Serialize
    }
    BinaryTree& operator=(const BinaryTree& copied) {
        if (&copied == this) {
            return *this;
        }
        // TODO(eden): Deserialize and then Serialize
        return *this;
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
        return TheRoot == nullptr;
    }
    constexpr int BiTreeSize() {
        return size;
    }

    ///@brief @b depth_related
    int BiTreeDepth_Rec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int left  = BiTreeDepth(node->left);
        int right = BiTreeDepth(node->right);
        int res   = std::max(left, right) + 1;
        return res;
    }
    int BiTreeDepth_Rec() {
        if (!TheRoot) {
            return 0;
        }
        return BiTreeDepth_Rec(TheRoot);
    }
    int BiTreeDepth_LevelOrder(Node* node) {
        int res = 0;

        if (node == nullptr) {
            return 0;
        }

        std::queue<Node*> queue;
        queue.push(node);

        while (!queue.empty()) {
            int currentLevelSize = static_cast<int>(queue.size());
            // iterate `currentLevel`
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = queue.front();
                queue.pop();
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            // finished iterating `currentLevel`, ++res
            ++res;
        }

        return res;
    }
    int BiTreeDepth_LevelOrder() {
        if (!TheRoot) {
            return 0;
        }
        return BiTreeDepth_LevelOrder(TheRoot);
    }
    int BiTreeDepth(Node* node) {
        return BiTreeDepth_LevelOrder(node);
    }
    int BiTreeDepth() {
        return BiTreeDepth_LevelOrder();
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
        return res;
    }
    Node* RightChild(Node* input) {
        Node* node = input;
        Node* res  = nullptr;
        while (node) {
            res  = node->right;
            node = node->right;
        }
        return res;
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
    void InsertChild(Node* curr_pos, BinaryTree<T>& toInsert, int LR = 0) {
        if (LR != 0 && LR != 1) {
            throw std::runtime_error("Unknown insert position type. ");
        }
        if (toInsert.TheRoot == nullptr) {
            throw std::runtime_error("toInsert is an empty tree!");
        }
        if (toInsert.TheRoot->right != nullptr) {
            throw std::runtime_error("toInsert has a right sub tree!");
        }

        size += toInsert.size;
        Node* original_sub_tree = nullptr;

        if (LR == 0) {
            original_sub_tree = curr_pos->left;
            curr_pos->left    = toInsert.TheRoot;
        } else {
            original_sub_tree = curr_pos->right;
            curr_pos->right   = toInsert.TheRoot;
        }

        toInsert.TheRoot->right = original_sub_tree;
    }
    void DeleteChild(Node* node, int LR = 0) {
        if (LR != 0 && LR != 1) {
            throw std::runtime_error("Unknown delete position type. ");
        }
        if (LR == 0) {
            PostOrderOpt(node->left, DeleteNode);
        } else {
            PostOrderOpt(node->right, DeleteNode);
        }
    }

    static BinaryTree<T>
    CreateBiTree_LevelOrder(const std::vector<std::string>& data)
    requires std::is_same_v<T, int> // only support int
    {
        Node* root = nullptr;

        if (data.empty()) {
            return nullptr;
        }

        std::queue<Node*> queue;
        bool              if_insert_to_left         = true;
        Node*             the_parent                = nullptr;
        int               num_of_inserted_to_parent = -1;
        int               num_of_node               = 0;

        for (const std::string& node_info : data) {
            Node* curr_node = (node_info == "#")
                ? nullptr
                : new Node(stoi(node_info));

            num_of_node += (node_info == "#") ? 0 : 1;

            queue.push(curr_node);

            // need to update parent
            if (num_of_inserted_to_parent == 2) {
                do {
                    queue.pop();
                    the_parent = queue.front();
                } while (!the_parent);

                num_of_inserted_to_parent = 0;
            }

            if (!the_parent) {
                root       = curr_node;
                the_parent = curr_node;
            } else {
                if (if_insert_to_left) {
                    the_parent->left = curr_node;
                } else {
                    the_parent->right = curr_node;
                }
                if_insert_to_left = !if_insert_to_left;
            }

            ++num_of_inserted_to_parent;
        }

        BinaryTree<T> res;
        res.TheRoot = root;
        res.size    = num_of_node;
        return res;
    }
    static BinaryTree<T>
    CreateBiTree(const std::vector<std::string>& data, Order order = Order::LevelOrder)
    requires std::is_same_v<T, int>      // only support int
        and (order == Order::LevelOrder) // only support LevelOrder
    {
        return CreateBiTree_LevelOrder(data);
    }
};

} // namespace DS