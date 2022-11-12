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
#include <type_traits>
#include <utility>
#include <vector>

namespace DS {

template <typename T>
requires std::equality_comparable<T>
class HuffmanTree {
    struct NodeInfo {
        T   value {};
        int index      = 0;
        int weight     = 0;
        int parent_idx = -1;
        int left_idx   = -1;
        int right_idx  = -1;
    };

    std::vector<NodeInfo> Table;

    int num_of_node         = 0;
    int num_of_initted_node = 0;

public:
    /// @brief @b alias
    using InitPairList = std::vector<std::pair<T, int>>;
    using InitList     = std::vector<int>;
    using InitPair     = std::pair<T, int>;

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
    }
    void preBuild(InitPairList& init) {
        int idx = 0;
        for (InitPair& pair : init) {
            NodeInfo& currNode = Table[idx];
            currNode.index     = idx;
            currNode.value     = pair.first;
            currNode.weight    = pair.second;
        }
    }
    std::pair<int, int> get_two_min_idx() {
        int min_idx        = 0;
        int second_min_idx = 0;
        for (int i = 1; i < num_of_initted_node; ++i) {
            NodeInfo& node_i          = Table[i];
            NodeInfo& node_min        = Table[min_idx];
            NodeInfo& node_second_min = Table[second_min_idx];
            if (node_i.value < node_min.value) {
                min_idx = i;
            }
            if (node_i.value >= node_min.value
                && node_i.value < node_second_min.value) {
                second_min_idx = i;
            }
        }
        return std::make_pair(min_idx, second_min_idx);
    }
    void build() {
        int insert_idx = num_of_initted_node;
        while (insert_idx < num_of_node) {
            int min_idx        = get_two_min_idx().first;
            int second_min_idx = get_two_min_idx().second;
            int parent_idx     = insert_idx;

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

    void Generate(InitPairList& init) {
        num_of_initted_node = init.size();
        unique(init);
        sort(init);
        alloc(init);
        preBuild(init);
        build();
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
};

} // namespace DS