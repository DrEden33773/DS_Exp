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
#include <unordered_map>
#include <utility>
#include <vector>

namespace DS {

template <typename T>
requires std::equality_comparable<T>
class HuffmanTree {
public:
    /// @brief @b alias
    using InitPairList = std::vector<std::pair<T, int>>;
    using InitList     = std::vector<int>;
    using InitPair     = std::pair<T, int>;
    using BitCodeType  = std::vector<char>;

private:
    static constexpr int DebugTableWidth = 12;
    struct NodeInfo {
        T   value {};
        int index      = 0;
        int weight     = 0;
        int parent_idx = -1;
        int left_idx   = -1;
        int right_idx  = -1;

        BitCodeType bit_code {};

        friend std::ostream& operator<<(std::ostream& out, const NodeInfo& self) {
            // index
            out << self.index;
            // value
            out << std::setw(DebugTableWidth) << self.value;
            // weight
            out << std::setw(DebugTableWidth) << self.weight;
            // parent_idx
            if (self.parent_idx != -1) {
                out << std::setw(DebugTableWidth) << self.parent_idx;
            } else {
                out << std::setw(DebugTableWidth) << "null";
            }
            // left_idx
            if (self.left_idx != -1) {
                out << std::setw(DebugTableWidth) << self.left_idx;
            } else {
                out << std::setw(DebugTableWidth) << "null";
            }
            // right_idx
            if (self.right_idx != -1) {
                out << std::setw(DebugTableWidth) << self.right_idx;
            } else {
                out << std::setw(DebugTableWidth) << "null";
            }
            // return
            return out;
        }
    };

    std::vector<NodeInfo>              NodeTable;
    std::unordered_map<T, BitCodeType> BitCodeMap;

    int num_of_initted_node = 0;
    int size_of_table       = 0;
    int num_of_input_node   = 0;

public:
    /// @brief @b tools
    void unique(InitPairList& init) {
        auto discarded_range_beg = std::unique(
            init.begin(), init.end(), [](const InitPair& a, const InitPair& b) {
                return a.first == b.first;
            }
        );
        init.erase(discarded_range_beg, init.end());
    }
    void sort(InitPairList& init) {
        std::sort(init.begin(), init.end(), [](const InitPair& a, const InitPair& b) {
            return a.second < b.second;
        });
    }
    void alloc(InitPairList& init) {
        int sizeof_init = init.size();
        int size        = 2 * sizeof_init - 1;
        NodeTable       = std::vector<NodeInfo>(size);
        size_of_table   = size;
    }
    void preBuild(InitPairList& init) {
        int idx = 0;
        for (InitPair& pair : init) {
            NodeInfo& currNode = NodeTable[idx];
            currNode.index     = idx;
            currNode.value     = pair.first;
            currNode.weight    = pair.second;
            ++idx;
        }
        while (idx < size_of_table) {
            NodeInfo& currNode = NodeTable[idx];
            currNode.index     = idx;
            ++idx;
        }
    }
    int get_min_without_ignored_idx(const int& ignored = -1) {
        int min_idx = 0;
        for (int i = 0; i < num_of_initted_node; ++i) {
            if (NodeTable[i].parent_idx != -1 || i == ignored) {
                continue;
            }
            min_idx = i;
            break;
        }
        for (int i = 0; i < num_of_initted_node; ++i) {
            if (NodeTable[i].parent_idx != -1 || i == ignored) {
                continue;
            }
            NodeInfo& curr_node = NodeTable[i];
            NodeInfo& min_node  = NodeTable[min_idx];
            if (curr_node.weight < min_node.weight) {
                min_idx = i;
            }
        }
        return min_idx;
    }
    void build() {
        int insert_idx = num_of_initted_node;
        while (insert_idx < size_of_table) {
            int min_idx        = get_min_without_ignored_idx();
            int second_min_idx = get_min_without_ignored_idx(min_idx);
            int parent_idx     = insert_idx;

            NodeInfo& node_min        = NodeTable[min_idx];
            NodeInfo& node_second_min = NodeTable[second_min_idx];
            NodeInfo& node_parent     = NodeTable[insert_idx];

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
        generate_bit_code();
        build_bit_code_map();
    }

    /// @brief @b constructors
    explicit HuffmanTree(InitPairList& init) { Generate(init); }
    explicit HuffmanTree(InitList& init)
    requires std::is_same_v<T, std::string>
        or std::is_same_v<T, int>
        or std::is_same_v<T, char>
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
        for (const NodeInfo& curr_node : NodeTable) {
            std::cout << curr_node;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    /// @brief @b View_the_CodeBitSet
    void EchoBitCode() {
        for (int idx = 0; idx < num_of_input_node; ++idx) {
            const NodeInfo& curr_node = NodeTable[idx];
            std::cout << curr_node.value;
            std::cout << " => ";
            for (auto code : curr_node.bit_code) {
                std::cout << static_cast<int>(code);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    /// @brief @b bit_code_generator
    int  get_root_idx() { return NodeTable.back().index; }
    int  get_left_idx(const int& in) { return NodeTable[in].left_idx; }
    int  get_right_idx(const int& in) { return NodeTable[in].right_idx; }
    void generate_bit_code() {
        if (!size_of_table) {
            return;
        }
        // BFS
        std::queue<int> queue;
        queue.push(get_root_idx());
        while (!queue.empty()) {
            int curr_layer_size = queue.size();
            while (curr_layer_size) {
                int curr_idx  = queue.front();
                int left_idx  = get_left_idx(curr_idx);
                int right_idx = get_right_idx(curr_idx);

                NodeInfo& curr  = NodeTable[curr_idx];
                NodeInfo& left  = NodeTable[left_idx];
                NodeInfo& right = NodeTable[right_idx];

                if (left_idx != -1) {
                    left.bit_code = curr.bit_code;
                    left.bit_code.push_back(0);
                    queue.push(left_idx);
                }
                if (right_idx != -1) {
                    right.bit_code = curr.bit_code;
                    right.bit_code.push_back(1);
                    queue.push(right_idx);
                }
                queue.pop();
                --curr_layer_size;
            }
        }
    }
    void build_bit_code_map() {
        for (int idx = 0; idx < num_of_input_node; ++idx) {
            const NodeInfo&    curr          = NodeTable[idx];
            const T&           curr_value    = curr.value;
            const BitCodeType& curr_bit_code = curr.bit_code;
            BitCodeMap.insert(std::make_pair(curr_value, curr_bit_code));
        }
    }
    auto get_bitcode_map() -> decltype(BitCodeMap) {
        return BitCodeMap;
    }
};

} // namespace DS