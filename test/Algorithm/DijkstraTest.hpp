/**
 * @file DijkstraTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../src/Algorithm/Dijkstra.hpp"
#include "../../src/DS/Graph.hpp"
#include "../../tools/TestTool.hpp"

namespace Test {

void DijkstraTest() {
    using VexSetType           = DS::Graph<long long>::VertexList;
    using WeightedEdgeListType = DS::Graph<long long>::WeightedEdgeList;

    VexSetType VexSet {
        0, 1, 2, 3, 4
    };
    WeightedEdgeListType WeightedEdgeList {
        std::make_tuple(0, 1, 2),
        std::make_tuple(1, 4, 7),
        std::make_tuple(0, 2, 6),
        std::make_tuple(2, 4, 2),
        std::make_tuple(0, 3, 9),
        std::make_tuple(3, 4, 2),
        std::make_tuple(1, 2, 3),
        std::make_tuple(2, 3, 1),
    };

    DS::Graph<long long> TestGraph {
        VexSet,
        WeightedEdgeList,
        true
    };
    Algo::Dijkstra<long long> DijkstraAlgorithm
        = Algo::Dijkstra<long long>::init(TestGraph);

    DijkstraAlgorithm.execute_algorithm(0);
    DijkstraAlgorithm.show_all_min_dist();
}

} // namespace Test