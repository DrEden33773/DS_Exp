/**
 * @file FloydTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../src/Algorithm/Floyd.hpp"
#include "../../src/DS/Graph.hpp"
#include "../../tools/TestTool.hpp"
#include <tuple>

namespace Test {

void FloydTest() {
    Tool::title_info("Floyd_Algorithm");

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
        Algo::Floyd<std::string> FloydAlgorithm(TestGraph);

        FloydAlgorithm.execute_algorithm();
        FloydAlgorithm.show_all_min_dist();
        FloydAlgorithm.show_all_min_route();
    }

    {
        using VexSetType           = DS::Graph<int>::VertexList;
        using WeightedEdgeListType = DS::Graph<int>::WeightedEdgeList;
        using std::make_tuple;

        VexSetType VexSet {
            0, 1, 2
        };
        WeightedEdgeListType WeightedEdgeList {
            make_tuple(0, 1, 4),
            make_tuple(1, 0, 6),
            make_tuple(0, 2, 11),
            make_tuple(2, 0, 3),
            make_tuple(1, 2, 2),
        };

        DS::Graph<int> TestGraph {
            VexSet,
            WeightedEdgeList,
            true
        };
        Algo::Floyd<int> FloydAlgorithm(TestGraph);

        FloydAlgorithm.execute_algorithm();
        FloydAlgorithm.show_all_min_dist();
        FloydAlgorithm.show_all_min_route();
    }

    Tool::end_info("Floyd_Algorithm");
}

} // namespace Test