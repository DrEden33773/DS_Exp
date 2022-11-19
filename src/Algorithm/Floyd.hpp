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
#include <utility>
#include <vector>

namespace Algo {

template <typename T>
class Floyd {
    template <typename U>
    using Matrix = std::vector<std::vector<U>>;
    template <typename U>
    using SubMatrix = std::vector<U>;

    DS::Graph<T>* Data = nullptr;
    int           size = 0;

    Matrix<int> Dist;
    Matrix<int> Adj;

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
    explicit Floyd<T>(DS::Graph<T>& graph)
        : Data(&graph)
        , size(graph.size) {
        // basic check
        Data->make_sure_non_empty();
        Data->make_sure_weighted();
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
};

} // namespace Algo