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
#include <iterator>
#include <list>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Algo {

template <typename T>
class Dijkstra {
    template <class K, class V>
    using HashMap = std::unordered_map<K, V>;

    DS::Graph<T>* Data       = nullptr;
    int           size       = 0;
    int           source_idx = 0;
    T             source {};

    std::vector<int> Dist; // min_dist of curr(index)-->source
    std::vector<int> Flag; // flag ( 0 or 1 )
    std::vector<int> Adj;  // Adj index

    std::unordered_map<T, std::list<T>> AllMinRoute;
    std::unordered_set<int>             NoRouteIdx;

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
            min_idx = (if_closer_judger(Dist[idx], Dist[min_idx])) ? idx : min_idx;
        }
        // 3. return
        return min_idx;
    }

    Dijkstra() = default;

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
        ret.Data->make_sure_non_empty();
        ret.Data->make_sure_weighted();
        // init Path
        for (int idx = 0; idx < graph.size; ++idx) {
            T vex = graph.Index_V_Map[idx];
            ret.AllMinRoute.insert(std::make_pair(vex, std::list<T>()));
        }
        return ret;
    }
    explicit Dijkstra<T>(DS::Graph<T>& graph)
        : Data(&graph)
        , size(graph.size) {
        Data->make_sure_non_empty();
        Data->make_sure_weighted();
        for (int idx = 0; idx < graph.size; ++idx) {
            T vex = graph.Index_V_Map[idx];
            AllMinRoute.insert(std::make_pair(vex, std::list<T>()));
        }
    }
    void execute_algorithm(const T& source) {
        // check
        Data->make_sure_has_vex(source);
        // bound
        const int& source_idx = Data->V_Index_Map[source];
        this->source_idx      = source_idx;
        this->source          = source;
        // 0. allocate space
        Adj  = std::vector<int>(Data->size);
        Dist = std::vector<int>(Data->size);
        Flag = std::vector<int>(Data->size, 0);
        // 1. init Dist
        for (int idx = 0; idx < Data->size; ++idx) {
            Dist[idx] = Data->Mat[source_idx][idx];
            Adj[idx]  = (Data->Mat[source_idx][idx] == Data->LIM) ? -1 : source_idx;
        }
        // 2. init flag
        Flag[source_idx] = 1;
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
                    Adj[curr]  = passed;
                }
            }
            // 4) update tag
            --unjoined_num;
        }
        // 4. update the Path
        for (int end_idx = 0; end_idx < size; ++end_idx) {
            T&            end_vex = Data->Index_V_Map[end_idx];
            std::list<T>& curr    = AllMinRoute.at(end_vex);

            int  trace_back_idx        = end_idx;
            bool if_no_route_to_source = false;

            while (trace_back_idx != source_idx) {

                int adj_idx = Adj[trace_back_idx];
                if (adj_idx == -1) {
                    curr.clear();
                    if_no_route_to_source = true;
                    break;
                }

                T& adj_vex = Data->Index_V_Map[adj_idx];

                curr.push_front(adj_vex);
                trace_back_idx = adj_idx;
            }

            if (if_no_route_to_source) {
                NoRouteIdx.insert(end_idx);
            }
        }
        for (int end_idx = 0; end_idx < size; ++end_idx) {
            if (NoRouteIdx.contains(end_idx)) {
                continue;
            }
            T&            end_vex = Data->Index_V_Map[end_idx];
            std::list<T>& curr    = AllMinRoute.at(end_vex);
            curr.push_back(end_vex);
        }
    }
    void show_all_min_dist() {
        for (int end_idx = 0; end_idx < size; ++end_idx) {
            T& end_vex = Data->Index_V_Map[end_idx];
            std::cout << "{ " << source << " -> " << end_vex << " } min distance : ";
            if (Dist[end_idx] == Data->LIM) {
                std::cout << "NaN";
            } else {
                std::cout << Dist[end_idx];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void show_all_min_route() {
        for (int end_idx = 0; end_idx < size; ++end_idx) {
            T&            end_vex    = Data->Index_V_Map[end_idx];
            std::list<T>& curr_route = AllMinRoute.at(end_vex);
            std::cout << "{ " << source << " -> " << end_vex << " } min route : ";
            std::for_each(
                curr_route.begin(),
                curr_route.end(),
                [](const T& vex) {
                    std::cout << vex << " ";
                }
            );
            if (!curr_route.size()) {
                std::cout << "No route!";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

} // namespace Algo