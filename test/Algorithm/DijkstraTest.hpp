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
    Tool::title_info("Dijkstra_Algorithm");
    // directed
    {
        using VexSetType           = DS::Graph<std::string>::VertexList;
        using WeightedEdgeListType = DS::Graph<std::string>::WeightedEdgeList;
        using std::make_tuple;

        VexSetType VexSet {
            "a", "b", "c", "d", "e"
        };
        WeightedEdgeListType WeightedEdgeList {
            make_tuple("a", "b", 2), // 2
            make_tuple("b", "e", 7), // 7
            make_tuple("a", "c", 6), // 6
            make_tuple("c", "e", 2), // 2
            make_tuple("a", "d", 9), // 9
            make_tuple("d", "e", 2), // 2
            make_tuple("b", "c", 3), // 3
            make_tuple("c", "d", 1), // 1
        };

        DS::Graph<std::string> TestGraph {
            VexSet,
            WeightedEdgeList,
            true
        };
        Algo::Dijkstra<std::string> DijkstraAlgorithm(TestGraph);

        DijkstraAlgorithm.execute_algorithm_from_source("a");
        DijkstraAlgorithm.show_all_min_dist();
        DijkstraAlgorithm.show_all_min_route();
    }
    // undirected
    {
        using VexSetType           = DS::Graph<int>::VertexList;
        using WeightedEdgeListType = DS::Graph<int>::WeightedEdgeList;
        using std::make_tuple;

        VexSetType VexSet {
            1, 2, 3, 4, 5, 6, 7
        };
        WeightedEdgeListType WeightedEdgeList {
            make_tuple(1, 4, 1),
            make_tuple(1, 6, 1),
            make_tuple(4, 5, 1),
            make_tuple(4, 7, 1),
            make_tuple(5, 2, 1),
            make_tuple(5, 3, 1),
        };

        DS::Graph<int> TestGraph {
            VexSet,
            WeightedEdgeList,
            false
        };
        Algo::Dijkstra<int> DijkstraAlgorithm(TestGraph);

        DijkstraAlgorithm.execute_algorithm_from_source(2);
        DijkstraAlgorithm.show_all_min_dist();
        DijkstraAlgorithm.show_all_min_route();
    }

    Tool::end_info("Dijkstra_Algorithm");
}

} // namespace Test