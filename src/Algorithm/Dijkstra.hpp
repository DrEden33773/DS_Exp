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
    DS::Graph<T>& Data;

    /* int source := initializer.source */
    int source = 0;
    /* int size := Data.size */
    int size = 0;

    std::vector<int> Path; // index of adj_vex_idx on the path
    std::vector<int> Dist; // min_dist of curr(index)-->source
    std::vector<int> Flag; // flag ( 0 or 1 )

    /* { end_vex : min_dist(source->end_vex) } */
    std::unordered_map<int, int> AllMinRoute;

    Dijkstra() = default;
    int find_closest_unjoined_idx() {
        int min_idx = 0;
        // 1. locate first available idx
        for (int idx = 0; idx < Data.size; ++idx) {
            if (Flag[idx]) {
                continue;
            }
            min_idx = idx;
            break;
        }
        // 2. find
        for (int idx = 0; idx < Data.size; ++idx) {
            if (Flag[idx]) {
                continue;
            }
            min_idx = (Dist[idx] < Dist[min_idx]) ? idx : min_idx;
        }
        // 3. return
        return min_idx;
    }

public:
    static Dijkstra<T> init(const DS::Graph<T>& graph) {
        Dijkstra<T> ret;
        ret.Data = graph;
    }

    void execute_algo(const int& source) {
        this->source = source;
        // 0. check
        Data.make_sure_has_index(source);
        Data.make_sure_undirected();
        Data.make_sure_weighted();
        // 1. init Dist
        for (int idx = 0; idx < Data.size; ++idx) {
            Data.Dist[idx] = Data.Mat[source][idx];
            Data.Path[idx] = (Data.Mat[source][idx] == Data.LIM) ? -1 : source;
        }
        // 2. init flag
        Flag[source] = 1;
        // 3. add all vex
        int unjoined_num = Data.size - 1;
        while (unjoined_num > 0) {
            // 1) find closest of `passed-->source`
            int passed = find_closest_unjoined_idx(); // for loop
            // 2) set visited
            Flag[passed] = 1;
            // 3) update all other dist
            for (int curr = 0; curr < Data.size; ++curr) {
                const int& curr_to_source   = Dist[curr];
                const int& curr_to_passed   = Data.Mat[curr][passed];
                const int& passed_to_source = Dist[passed];

                // curr-->passed-->source < curr-->source
                bool if_unvisited = Flag[curr] == 0;
                bool if_closer    = curr_to_source > curr_to_passed + passed_to_source;

                if (if_unvisited && if_closer) {
                    // need to update
                    Dist[curr] = curr_to_passed + passed_to_source;
                    Path[curr] = passed;
                }
            }
            // 4) update tag
            --unjoined_num;
        }
        // 4. store

        // 1. all min route val
        for (int curr = 0; curr < size; ++curr) {
            AllMinRoute[curr] = Dist[curr];
        }
        // 2. all min route detail
    }
    void execute_algorithm(const T& source) {
        // 0. check
        Data.make_sure_has_vex(source);
        // 1. trans
        execute_algo(Data.V_Index_Map[source]);
    }
    void show_all_min_dist() {
        T& source_vex = Data.V_Index_Map[source];
        for (auto&& pair : AllMinRoute) {
            T&  end_vex  = Data.V_Index_Map[pair.first];
            int min_dist = pair.second;
            std::cout << "{ " << source_vex << " -> " << end_vex << " } : ";
            std::cout << min_dist;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

} // namespace Algo