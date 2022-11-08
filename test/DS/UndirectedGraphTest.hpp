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
    using StrConstructor = DS::UndirectedGraph<std::string>::ConstructList;
    using StrGraph       = DS::UndirectedGraph<std::string>;

    StrConstructor init {
        std::make_pair("a", "b"),
        std::make_pair("c", "d"),
        std::make_pair("a", "c"),
        std::make_pair("b", "d"),
        std::make_pair("a", "e"),
        std::make_pair("b", "e"),
        std::make_pair("c", "f"),
    };

    StrGraph test1(init);

    test1.EchoVIndexTable();
    std::cout << std::endl;

    test1.BFSTraverse();
    std::cout << std::endl;

    test1.DFSTraverse();
    std::cout << std::endl;
}

} // namespace Test