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
#include <iomanip>
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
    static constexpr int DEBUG_WIDTH = 10;

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

    bool if_closer_judger(
        int joined_to_curr,
        int source_to_curr
    ) {
        bool res = false;
        // joined_to_curr < source_to_curr
        // b < c
        const int& b            = joined_to_curr;
        const int& c            = source_to_curr;
        bool       if_b_lim     = b == Data->LIM;
        bool       if_c_lim     = c == Data->LIM;
        bool       if_bc_no_lim = !if_b_lim && !if_c_lim;
        if (if_bc_no_lim) {
            res = ((b) < (c));
        } else {
            if (!if_b_lim && if_c_lim) {
                res = true;
            }
            // all cases else should be `false`
        }
        return res;
    }

public:
    explicit Prim(DS::Graph<T>& graph)
        : Data(&graph)
        , size(graph.size) {
        Data->make_sure_non_empty();
        Data->make_sure_weighted();
        // actually, should add `make_sure_fully_connected`
    }
    void execute_algorithm(const T& source) {
        // check
        Data->make_sure_has_vex(source);
        // bound
        const int& source_idx = Data->V_Index_Map[source];
        this->source_idx      = source_idx;
        this->source          = source;
        // 0. allocate space
        Adj     = std::vector<int>(Data->size);
        LowCost = std::vector<int>(Data->size);
        Flag    = std::vector<int>(Data->size, 0);
        // 1. init Dist
        for (int idx = 0; idx < Data->size; ++idx) {
            LowCost[idx] = Data->Mat[source_idx][idx];
            Adj[idx]     = (Data->Mat[source_idx][idx] == Data->LIM) ? -1 : source_idx;
        }
        // 2. init flag
        Flag[source_idx] = 1;
        // 3. add all vex
        int unjoined_num = Data->size - 1;
        while (unjoined_num > 0) {
            // 1) find closest of `passed-->source`
            int joined = find_closest_unjoined_idx(); // for loop
            // 2) set visited
            Flag[joined] = 1;
            // 3) update all other dist
            for (int curr = 0; curr < Data->size; ++curr) {
                int  source_to_curr = Data->Mat[source_idx][curr];
                int  joined_to_curr = Data->Mat[joined][curr];
                bool if_unvisited   = Flag[curr] == 0;
                bool if_closer      = if_closer_judger(
                    joined_to_curr,
                    source_to_curr
                );
                if (if_unvisited && if_closer) {
                    // need to update
                    LowCost[curr] = joined_to_curr;
                    Adj[curr]     = joined;
                }
            }
            // 4) update tag
            --unjoined_num;
        }
    }
    void Debug_Echo_Table() {
        // Vex
        std::cout << std::setw(DEBUG_WIDTH) << "Vex";
        for (int idx = 0; idx < size; ++idx) {
            T& vex = Data->Index_V_Map[idx];
            std::cout << std::setw(DEBUG_WIDTH) << vex;
        }
        std::cout << std::endl;

        // AdjVex
        std::cout << std::setw(DEBUG_WIDTH) << "AdjVex";
        for (int idx = 0; idx < size; ++idx) {
            int adj_idx = Adj[idx];
            if (adj_idx != Data->LIM) {
                T& vex = Data->Index_V_Map[adj_idx];
                std::cout << std::setw(DEBUG_WIDTH) << vex;
            } else {
                std::cout << std::setw(DEBUG_WIDTH) << "Nil";
            }
        }
        std::cout << std::endl;

        // LowCost
        std::cout << std::setw(DEBUG_WIDTH) << "LowCost";
        for (int idx = 0; idx < size; ++idx) {
            int curr_cost = LowCost[idx];
            if (curr_cost != Data->LIM) {
                std::cout << std::setw(DEBUG_WIDTH) << curr_cost;
            } else {
                std::cout << std::setw(DEBUG_WIDTH) << "NaN";
            }
        }
        std::cout << std::endl;

        // println
        std::cout << std::endl;
    }
};

} // namespace Algo