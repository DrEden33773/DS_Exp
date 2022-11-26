/**
 * @file Floyd.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Floyd Algorithm for Graph
 * @version 0.1
 * @date 2022-11-18
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
#include <unordered_set>
#include <utility>
#include <vector>

namespace Algo {

template <typename T>
class Floyd {
    template <typename U>
    using Matrix = std::vector<std::vector<U>>;
    template <typename U>
    using SubMatrix = std::vector<U>;

    using IntPair = std::pair<int, int>;
    using VexList = std::list<T>;
    struct IntPairHash {
        std::size_t operator()(const IntPair& s) const {
            std::size_t h1 = std::hash<int> {}(s.first);
            std::size_t h2 = std::hash<int> {}(s.second);
            return h1 ^ (h2 << 1);
        }
    };

    DS::Graph<T>* Data = nullptr;
    int           size = 0;

    Matrix<int> Dist;
    Matrix<int> Adj;

    std::unordered_map<IntPair, VexList, IntPairHash> AllMinRoute;
    std::unordered_set<IntPair, IntPairHash>          NoRouteIdxPair;

private:
    bool if_closer_judger(
        int source_to_passed,
        int passed_to_end,
        int source_to_end
    ) {
        bool res = false;
        // source_to_passed + passed_to_end < source_to_end
        // a + b < c
        const int& a             = source_to_passed;
        const int& b             = passed_to_end;
        const int& c             = source_to_end;
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

    Floyd() = default;

public:
    explicit Floyd(DS::Graph<T>& graph)
        : Data(&graph)
        , size(graph.size) {
        // basic check
        Data->make_sure_non_empty();
        Data->make_sure_weighted();
        Data->make_sure_directed();
        // init `Adj` and `Dist`
        Dist = Matrix<int>(size, SubMatrix<int>(size, 0));
        Adj  = Matrix<int>(size, SubMatrix<int>(size, 0));
        for (int source = 0; source < size; ++source) {
            for (int end = 0; end < size; ++end) {
                int source_to_end = Data->Mat[source][end];
                Dist[source][end] = source_to_end;
                if (source_to_end != Data->LIM) {
                    Adj[source][end] = source;
                } else {
                    Adj[source][end] = -1;
                }
            }
        }
    }
    void build_all_min_route() {
        for (int source = 0; source < size; ++source) {
            for (int end = 0; end < size; ++end) {
                auto key_pair   = std::make_pair(source, end);
                T&   end_vex    = Data->Index_V_Map[end];
                T&   source_vex = Data->Index_V_Map[source];

                std::list<T>& curr_route = AllMinRoute[key_pair];

                int  trace_back_idx        = end;
                bool if_no_route_to_source = false;
                while (trace_back_idx != source) {
                    int adj_idx = Adj[source][trace_back_idx];
                    if (adj_idx == -1) {
                        curr_route.clear();
                        if_no_route_to_source = true;
                        break;
                    }
                    T& adj_vex = Data->Index_V_Map[adj_idx];
                    curr_route.push_front(adj_vex);
                    trace_back_idx = adj_idx;
                }
                if (if_no_route_to_source) {
                    NoRouteIdxPair.insert(key_pair);
                }
            }
            for (int end = 0; end < size; ++end) {
                auto key_pair = std::make_pair(source, end);
                if (NoRouteIdxPair.contains(key_pair)) {
                    continue;
                }
                T&            end_vex    = Data->Index_V_Map[end];
                std::list<T>& curr_route = AllMinRoute.at(key_pair);
                curr_route.push_back(end_vex);
            }
        }
    }
    void execute_algorithm() {
        for (int passed = 0; passed < size; ++passed) {
            for (int source = 0; source < size; ++source) {
                for (int end = 0; end < size; ++end) {
                    int source_to_end    = Dist[source][end];
                    int source_to_passed = Dist[source][passed];
                    int passed_to_end    = Dist[passed][end];
                    if (if_closer_judger(
                            source_to_passed,
                            passed_to_end,
                            source_to_end
                        )) {
                        Dist[source][end] = source_to_passed + passed_to_end;
                        Adj[source][end]  = passed;
                    }
                }
            }
        }
        // could store the path
        build_all_min_route();
    }
    void show_all_min_dist() {
        for (int source = 0; source < size; ++source) {
            for (int end = 0; end < size; ++end) {
                T& src = Data->Index_V_Map[source];
                T& ed  = Data->Index_V_Map[end];
                std::cout << "{ " << src << " -> " << ed << " } min distance : ";
                if (Dist[source][end] == Data->LIM) {
                    std::cout << "NaN" << std::endl;
                } else {
                    std::cout << Dist[source][end] << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
    void show_all_min_route() {
        for (int source = 0; source < size; ++source) {
            for (int end = 0; end < size; ++end) {
                auto key_pair = std::make_pair(source, end);
                T&   src      = Data->Index_V_Map[source];
                T&   ed       = Data->Index_V_Map[end];

                std::list<T>& curr_route = AllMinRoute.at(key_pair);
                std::cout << "{ " << src << " -> " << ed << " } min route : ";
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
        }
        std::cout << std::endl;
    }
};

} // namespace Algo