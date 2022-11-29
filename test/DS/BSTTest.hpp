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

namespace Test {

void BSTTest() {
    Tool::title_info("Binary_Search_Tree");

    DS::BST<int> BST;

    std::vector<int> InsertList {
        76, 50, 80, 30,
        60, 78, 90, 5,
        40, 55, 70, 35,
        54, 73, 71, 72
    };

    for (auto&& insert : InsertList) {
        BST.insert(insert);
    }

    BST.print_tree();

    BST.remove(90); // easy
    BST.remove(40); // medium
    BST.remove(60); // hard
    BST.remove(76);
    BST.remove(50);

    // success

    BST.print_tree();

    Tool::end_info("Binary_Search_Tree");
}

} // namespace Test