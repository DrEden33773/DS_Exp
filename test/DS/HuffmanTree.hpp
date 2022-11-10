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
#include <type_traits>
#include <utility>
#include <vector>

namespace DS {

template <typename T>
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
    int                   NumOfNode = 0;

    HuffmanTree() = default;

public:
    using InitPairList = std::vector<std::pair<T, int>>;
    using InitList     = std::vector<int>;
    using InitPair     = std::pair<T, int>;
    void Generate(InitPairList& init) {
        // 1. unique by name
        auto discarded_range_beg = std::unique(
            init.begin(),
            init.end(),
            [](const InitPair& a, const InitPair& b) {
                return a.first == b.first;
            }
        );
        init.erase(discarded_range_beg, init.end());
        // 2. sort by weight(ascending)
        std::sort(
            init.begin(),
            init.end(),
            [](const InitPair& a, const InitPair& b) {
                return a.second < b.second;
            }
        );
        // 3. alloc space for Table (with initialize)
        size_t sizeof_init = init.size();
        size_t size        = 2 * sizeof_init - 1;
        Table              = std::vector<NodeInfo>(size);
        // 4. push into the table
        int idx = 0;
        for (InitPair& pair : init) {
            NodeInfo& currNode = Table[idx];
            currNode.index     = idx;
            currNode.value     = pair.first;
            currNode.weight    = pair.second;
        }
    }
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