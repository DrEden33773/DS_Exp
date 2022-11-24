/**
 * @file BSTTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../src/DS/BST.hpp"
#include "../../tools/TestTool.hpp"
#include <string>
#include <vector>

namespace Test {

void BSTTest() {
    Tool::title_info("Binary_Search_Tree");

    DS::BST<int> BST;

    BST.insert(1);
    BST.insert(1);
    BST.insert(4);
    BST.insert(4);
    BST.insert(3);
    BST.insert(2);
    BST.insert(2);
    BST.insert(5);

    BST.print_tree();

    Tool::end_info("Binary_Search_Tree");
}

} // namespace Test