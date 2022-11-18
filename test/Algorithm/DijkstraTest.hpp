/**
 * @file DijkstraTest.hpp
 * @author Eden (edwardwang@gmail.com)
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
    using VexSetType           = DS::Graph<std::string>::VertexList;
    using WeightedEdgeListType = DS::Graph<std::string>::WeightedEdgeList;

    VexSetType VexSet {
        "a", "b", "c", "d", "e"
    };
    WeightedEdgeListType WeightedEdgeList {
        std::make_tuple("a", "b", 2), // 2
        std::make_tuple("b", "e", 7), // 7
        std::make_tuple("a", "c", 6), // 6
        std::make_tuple("c", "e", 2), // 2
        std::make_tuple("a", "d", 9), // 9
        std::make_tuple("d", "e", 2), // 2
        std::make_tuple("b", "c", 3), // 3
        std::make_tuple("c", "d", 1), // 1
    };

    DS::Graph<std::string> TestGraph {
        VexSet,
        WeightedEdgeList,
        true
    };
    Algo::Dijkstra<std::string> DijkstraAlgorithm(TestGraph);

    DijkstraAlgorithm.execute_algorithm("a");
    DijkstraAlgorithm.show_all_min_dist();
    DijkstraAlgorithm.show_all_min_route();
}

} // namespace Test