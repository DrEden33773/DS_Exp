/**
 * @file UndirectedGraphTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief UndirectedGraphTest
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../src/DS/UndirectedGraph.hpp"
#include "../../tools/TestTool.hpp"

#include <string>
#include <utility>
#include <vector>

namespace Test {

void UndirectedGraphTest() {
    using String_EdgeList = DS::UndirectedGraph<std::string>::EdgeList;
    using String_VexList  = DS::UndirectedGraph<std::string>::VertexList;
    using StrGraph        = DS::UndirectedGraph<std::string>;

    String_VexList VexList {
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
    };

    String_EdgeList EdgeList {
        std::make_pair("a", "b"),
        std::make_pair("c", "d"),
        std::make_pair("a", "c"),
        std::make_pair("b", "d"),
        std::make_pair("a", "e"),
        std::make_pair("b", "e"),
        std::make_pair("c", "f"),
    };

    StrGraph test1(VexList, EdgeList);

    test1.EchoVIndexTable();
    std::cout << std::endl;

    test1.BFSTraverse();
    std::cout << std::endl;

    test1.DFSTraverse();
    std::cout << std::endl;
}

} // namespace Test