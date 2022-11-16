/**
 * @file HuffmanTreeTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief HuffmanTreeTest
 * @version 0.1
 * @date 2022-11-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../src/DS/HuffmanTree.hpp"
#include "../../tools/TestTool.hpp"
#include <string>
#include <utility>

namespace Test {

void HuffmanTreeTest() {
    Tool::title_info("Huffman_Tree");

    using InitListType = DS::HuffmanTree<char>::InitPairList;

    InitListType InitList {
        std::make_pair('a', 1),
        std::make_pair('e', 2),
        std::make_pair('i', 5),
        std::make_pair('s', 3),
        std::make_pair('t', 4),
    };

    DS::HuffmanTree<char> TestHuffmanTree(InitList);

    TestHuffmanTree.EchoInTable();
    TestHuffmanTree.EchoBitCode();

    Tool::end_info("Huffman_Tree");
}

} // namespace Test