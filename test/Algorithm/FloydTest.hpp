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

namespace Test {

void FloydTest() {
    Tool::title_info("Floyd_Algorithm");

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
    Algo::Floyd<std::string> FloydAlgorithm(TestGraph);

    FloydAlgorithm.execute_algorithm();
    FloydAlgorithm.show_all_min_dist();

    Tool::end_info("Floyd_Algorithm");
}

} // namespace Test