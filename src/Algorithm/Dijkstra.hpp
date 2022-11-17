/**
 * @file Dijkstra.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Dijkstra Algorithm Manager
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../DS/Graph.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Algo {

template <typename T>
class Dijkstra {
    DS::Graph<T>* Data = nullptr;

    /* int source := initializer.source */
    int source = 0;
    /* int size := Data->size */
    int size = 0;

    std::vector<int> Path; // index of adj_vex_idx on the path
    std::vector<int> Dist; // min_dist of curr(index)-->source
    std::vector<int> Flag; // flag ( 0 or 1 )

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
            if (Dist[idx] == Data->LIM) {
                continue;
            }
            min_idx = (Dist[idx] < Dist[min_idx]) ? idx : min_idx;
        }
        // 3. return
        return min_idx;
    }

    Dijkstra() { }

    // source_to_passed + passed_to_curr < source_to_curr
    bool if_closer_judger(
        int source_to_passed,
        int passed_to_curr,
        int source_to_curr
    ) {
        bool res = false;
        // source_to_passed + passed_to_curr < source_to_curr
        // a + b < c
        const int& a             = source_to_passed;
        const int& b             = passed_to_curr;
        const int& c             = source_to_curr;
        bool       if_a_lim      = a == Data->LIM;
        bool       if_b_lim      = b == Data->LIM;
        bool       if_c_lim      = c == Data->LIM;
        bool       if_ab_no_lim  = !if_a_lim && !if_b_lim;
        bool       if_abc_no_lim = !if_a_lim && !if_b_lim && !if_c_lim;
        if (if_abc_no_lim) {
            res = ((a + b) < (c));
        } else {
            if (if_ab_no_lim && if_c_lim) {
                res = true;
            }
            // all cases else should be `false`
        }
        return res;
    }

public:
    static Dijkstra<T> init(DS::Graph<T>& graph) {
        Dijkstra<T> ret;
        ret.Data = &graph;
        ret.size = graph.size;
        return ret;
    }

    void execute_algorithm(const int& source) {
        this->source = source;
        // -1. check
        Data->make_sure_non_empty();
        Data->make_sure_has_index(source);
        Data->make_sure_weighted();
        // 0. allocate space
        Path = std::vector<int>(Data->size);
        Dist = std::vector<int>(Data->size);
        Flag = std::vector<int>(Data->size, 0);
        // 1. init Dist
        for (int idx = 0; idx < Data->size; ++idx) {
            Dist[idx] = Data->Mat[source][idx];
            Path[idx] = (Data->Mat[source][idx] == Data->LIM) ? -1 : source;
        }
        // 2. init flag
        Flag[source] = 1;
        // 3. add all vex
        int unjoined_num = Data->size - 1;
        while (unjoined_num > 0) {
            // 1) find closest of `passed-->source`
            int passed = find_closest_unjoined_idx(); // for loop
            // 2) set visited
            Flag[passed]         = 1;
            int source_to_passed = Dist[passed];
            if (source_to_passed == Data->LIM) {
                continue;
            }
            // 3) update all other dist
            for (int curr = 0; curr < Data->size; ++curr) {
                int source_to_curr = Dist[curr];
                int passed_to_curr = Data->Mat[passed][curr];

                // source->passed->curr < source-->curr
                bool if_unvisited = Flag[curr] == 0;
                bool if_closer    = if_closer_judger(
                    source_to_passed, /* a */
                    passed_to_curr,   /* b */
                    source_to_curr    /* c */
                    /* Judge => a + b < c (consider LIM)*/
                );

                if (if_unvisited && if_closer) {
                    // need to update
                    Dist[curr] = source_to_passed + passed_to_curr;
                    Path[curr] = passed;
                }
            }
            // 4) update tag
            --unjoined_num;
        }
        // 4. store
    }
    void execute_algorithm(const T& source) {
        // 0. check
        Data->make_sure_has_vex(source);
        // 1. trans
        execute_algorithm(Data->V_Index_Map[source]);
    }
    void show_all_min_dist() {
        T& source_vex = Data->Index_V_Map[source];
        for (int end_idx = 0; end_idx < size; ++end_idx) {
            T& end_vex = Data->Index_V_Map[end_idx];
            std::cout << "{ " << source_vex << " -> " << end_vex << " } : ";
            std::cout << Dist[end_idx];
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

} // namespace Algo