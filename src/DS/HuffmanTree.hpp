/**
 * @file HuffmanTree.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief HuffmanTree
 * @version 0.1
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <concepts>
#include <functional>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

namespace DS {

template <typename T>
requires std::equality_comparable<T>
class HuffmanTree {
    static constexpr int DebugTableWidth = 12;
    struct NodeInfo {
        T   value {};
        int index      = 0;
        int weight     = 0;
        int parent_idx = -1;
        int left_idx   = -1;
        int right_idx  = -1;

        std::vector<bool> bitset_code {};

        friend std::ostream& operator<<(std::ostream& out, const NodeInfo& self) {
            out << self.index;
            out << std::setw(DebugTableWidth) << self.value;
            out << std::setw(DebugTableWidth) << self.weight;
            if (self.parent_idx != -1) {
                out << std::setw(DebugTableWidth) << self.parent_idx;
            } else {
                out << std::setw(DebugTableWidth) << "null";
            }
            if (self.left_idx != -1) {
                out << std::setw(DebugTableWidth) << self.left_idx;
            } else {
                out << std::setw(DebugTableWidth) << "null";
            }
            if (self.right_idx != -1) {
                out << std::setw(DebugTableWidth) << self.right_idx;
            } else {
                out << std::setw(DebugTableWidth) << "null";
            }
            return out;
        }
    };

    std::vector<NodeInfo> Table;

    size_t num_of_initted_node = 0;
    size_t size_of_table       = 0;
    size_t num_of_input_node   = 0;

public:
    /// @brief @b alias
    using InitPairList = std::vector<std::pair<T, int>>;
    using InitList     = std::vector<int>;
    using InitPair     = std::pair<T, int>;

    /// @brief @b tools
    void unique(InitPairList& init) {
        auto discarded_range_beg = std::unique(
            init.begin(),
            init.end(),
            [](const InitPair& a, const InitPair& b) {
                return a.first == b.first;
            }
        );
        init.erase(discarded_range_beg, init.end());
    }
    void sort(InitPairList& init) {
        std::sort(
            init.begin(),
            init.end(),
            [](const InitPair& a, const InitPair& b) {
                return a.second < b.second;
            }
        );
    }
    void alloc(InitPairList& init) {
        size_t sizeof_init = init.size();
        size_t size        = 2 * sizeof_init - 1;
        Table              = std::vector<NodeInfo>(size);
        size_of_table      = size;
    }
    void preBuild(InitPairList& init) {
        size_t idx = 0;
        for (InitPair& pair : init) {
            NodeInfo& currNode = Table[idx];
            currNode.index     = idx;
            currNode.value     = pair.first;
            currNode.weight    = pair.second;
            ++idx;
        }
        while (idx < size_of_table) {
            NodeInfo& currNode = Table[idx];
            currNode.index     = idx;
            ++idx;
        }
    }
    std::pair<int, int> get_two_min_idx() {
        size_t min_idx        = 0;
        size_t second_min_idx = 0;
        // 1. init min_idx && second_min_idx correctly
        // need to ignore { node | node.parent_idx != -1 }
        for (size_t i = 0; i < num_of_initted_node; ++i) {
            if (Table[i].parent_idx != -1) {
                continue;
            }
            min_idx = i;
            break;
        }
        for (size_t i = 0; i < num_of_initted_node; ++i) {
            if (Table[i].parent_idx != -1) {
                continue;
            }
            int curr_weight = Table[i].weight;
            int min_weight  = Table[min_idx].weight;
            if (curr_weight != min_weight) {
                second_min_idx = i;
                break;
            }
        }
        // 2. start to find
        for (size_t i = 0; i < num_of_initted_node; ++i) {
            if (Table[i].parent_idx != -1) {
                continue;
            }
            NodeInfo& curr_node = Table[i];
            NodeInfo& min_node  = Table[min_idx];
            if (curr_node.weight < min_node.weight) {
                min_idx = i;
            }
        }
        for (size_t i = 0; i < num_of_initted_node; ++i) {
            if (Table[i].parent_idx != -1) {
                continue;
            }
            NodeInfo& curr_node       = Table[i];
            NodeInfo& min_node        = Table[min_idx];
            NodeInfo& second_min_node = Table[second_min_idx];
            if (curr_node.weight < second_min_node.weight
                && curr_node.weight > min_node.weight) {
                second_min_idx = i;
            }
        }
        return std::make_pair(min_idx, second_min_idx);
    }
    void build() {
        int insert_idx = num_of_initted_node;
        while (insert_idx < size_of_table) {
            size_t min_idx        = get_two_min_idx().first;
            size_t second_min_idx = get_two_min_idx().second;
            size_t parent_idx     = insert_idx;

            NodeInfo& node_min        = Table[min_idx];
            NodeInfo& node_second_min = Table[second_min_idx];
            NodeInfo& node_parent     = Table[insert_idx];

            node_min.parent_idx        = parent_idx;
            node_second_min.parent_idx = parent_idx;

            node_parent.weight    = node_min.weight + node_second_min.weight;
            node_parent.left_idx  = min_idx;
            node_parent.right_idx = second_min_idx;

            ++num_of_initted_node;
            ++insert_idx;
        }
    }

    /// @brief @b TreeGenerator
    void Generate(InitPairList& init) {
        num_of_input_node   = init.size();
        num_of_initted_node = init.size();
        unique(init);
        sort(init);
        alloc(init);
        preBuild(init);
        build();
        generate_bitset_code();
    }

    /// @brief @b constructors
    explicit HuffmanTree(InitPairList& init) {
        Generate(init);
    }
    explicit HuffmanTree(InitList& init)
    requires std::is_same_v<T, std::string> or std::is_same_v<T, int>
    {
        InitPairList true_init;
        true_init.reserve(init.size());
        for (auto&& weight : init) {
            true_init.emplace_back(std::make_pair(weight, weight));
        }
        Generate(true_init);
    }

    /// @brief @b View_the_table
    void EchoInTable() {
        // index | value | weight | parent_idx | left_idx | right_idx
        std::cout << "index";
        std::cout << std::setw(DebugTableWidth) << "value";
        std::cout << std::setw(DebugTableWidth) << "weight";
        std::cout << std::setw(DebugTableWidth) << "parent_idx";
        std::cout << std::setw(DebugTableWidth) << "left_idx";
        std::cout << std::setw(DebugTableWidth) << "right_idx";
        std::cout << std::endl;
        std::cout << std::endl;
        for (const NodeInfo& curr_node : Table) {
            std::cout << curr_node;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    /// @brief @b View_the_CodeBitSet
    void EchoCodeBitSet() {
        for (size_t idx = 0; idx < num_of_input_node; ++idx) {
            const NodeInfo& curr_node = Table[idx];
            std::cout << curr_node.value;
            std::cout << " => ";
            for (auto code : curr_node.bitset_code) {
                std::cout << static_cast<int>(code);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    /// @brief @b bitset_code_generator
    int get_root_idx() {
        return Table.back().index;
    }
    int get_left_idx(const size_t& in) {
        return Table[in].left_idx;
    }
    int get_right_idx(const size_t& in) {
        return Table[in].right_idx;
    }
    void generate_bitset_code() {
        if (!size_of_table) {
            return;
        }
        // BFS
        std::queue<int> queue;
        queue.push(get_root_idx());
        while (!queue.empty()) {
            size_t curr_layer_size = queue.size();
            while (curr_layer_size) {
                int curr  = queue.front();
                int left  = get_left_idx(curr);
                int right = get_right_idx(curr);
                if (left != -1) {
                    Table[left].bitset_code = Table[curr].bitset_code;
                    Table[left].bitset_code.push_back(0);
                    queue.push(left);
                }
                if (right != -1) {
                    Table[right].bitset_code = Table[curr].bitset_code;
                    Table[right].bitset_code.push_back(1);
                    queue.push(right);
                }
                queue.pop();
                --curr_layer_size;
            }
        }
    }
};

} // namespace DS