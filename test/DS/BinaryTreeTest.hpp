/**
 * @file BinaryTreeTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief BinaryTreeTest
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../src/DS/BinaryTree.hpp"
#include "../../tools/TestTool.hpp"
#include <ios>

namespace Test {

void first_test() {
    std::cout << std::boolalpha;

    DS::BinaryTree<int> BiTree_1_2_3
        = DS::BinaryTree<int>::CreateBiTree(
            std::vector<std::string> { "1", "2", "3" }
        );
    DS::BinaryTree<int> BiTree_1_2_3_with_null_layer
        = DS::BinaryTree<int>::CreateBiTree(
            std::vector<
                std::string> { "1", "2", "3", "#", "#", "#", "#" }
        );
    BiTree_1_2_3.LevelOrderTraverse();
    std::cout << std::endl;
    BiTree_1_2_3_with_null_layer.LevelOrderTraverse();
    std::cout << std::endl;

    std::cout << "If BiTree_1_2_3 Complete => " << BiTree_1_2_3.IfCompleteBiTree() << std::endl;

    BiTree_1_2_3.emplace_unselect(
        [](int a) -> bool {
            return a == 2;
        }
    );
    BiTree_1_2_3_with_null_layer.emplace_unselect(
        [](int a) -> bool {
            return a == 3;
        }
    );
    BiTree_1_2_3.LevelOrderTraverse();
    std::cout << std::endl;
    BiTree_1_2_3_with_null_layer.LevelOrderTraverse();
    std::cout << std::endl;

    std::cout << "If BiTree_1_2_3 Complete => " << BiTree_1_2_3.IfCompleteBiTree() << std::endl;

    std::cout << std::endl;
}

void BinaryTreeTest() {
    Tool::title_info("Binary_Tree");

    first_test();

    Tool::end_info("Binary_Tree");
}

} // namespace Test