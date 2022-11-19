/**
 * @file Prim.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../DS/Graph.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Algo {

template <typename T>
class Prim {
    DS::Graph<T>* Data       = nullptr;
    int           size       = 0;
    int           source_idx = 0;
    T             source {};

    std::vector<int> LowCost; // min_dist of curr(index)-->joined
    std::vector<int> Flag;    // flag ( 0 or 1 )
    std::vector<int> Adj;     // Adj index

    std::list<T> MSTPath;

    int find_closest_unjoined_idx() {
        int min_idx = 0;
        // 1. locate first available idx
        for (int idx = 0; idx < Data->size; ++idx) {
            if (Flag[idx]) {
                continue;
            }
            min_idx = idx;
            break;
        }
        // 2. find
        for (int idx = 0; idx < Data->size; ++idx) {
            if (Flag[idx]) {
                continue;
            }
            if (LowCost[idx] == Data->LIM) {
                continue;
            }
            min_idx = (LowCost[idx] < LowCost[min_idx]) ? idx : min_idx;
        }
        // 3. return
        return min_idx;
    }

    Prim() = default;

public:
    explicit Prim(DS::Graph<T>& graph)
        : Data(&graph)
        , size(graph.size) {
        Data->make_sure_non_empty();
        Data->make_sure_weighted();
    }
};

} // namespace Algo