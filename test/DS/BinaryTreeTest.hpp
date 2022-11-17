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

    DS::BinaryTree<int> BiTree = DS::BinaryTree<int>::CreateBiTree(
        std::vector<std::string> {
            "1", "2", "3",
            "4", "5", "6",
            "7" }
    );
    DS::BinaryTree<int> BiTree_copied = BiTree;

    BiTree.LevelOrderTraverse();
    std::cout << std::endl;
    BiTree_copied.LevelOrderTraverse();
    std::cout << std::endl;

    std::cout << "If BiTree Complete => "
              << BiTree.IfCompleteBiTree()
              << std::endl;

    BiTree.emplace_unselect(
        [](int a) -> bool {
            return a == 2;
        }
    );
    BiTree_copied.emplace_unselect(
        [](int a) -> bool {
            return a == 3;
        }
    );
    BiTree.LevelOrderTraverse();
    std::cout << std::endl;
    BiTree_copied.LevelOrderTraverse();
    std::cout << std::endl;

    std::cout << "If BiTree Complete => "
              << BiTree.IfCompleteBiTree()
              << std::endl;

    std::cout << std::endl;
}

void BinaryTreeTest() {
    Tool::title_info("Binary_Tree");

    first_test();

    Tool::end_info("Binary_Tree");
}

} // namespace Test