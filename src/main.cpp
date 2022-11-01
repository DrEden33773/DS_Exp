/**
 * @file main.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief main file
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../test/TestIter.hpp"
#include "DS/BinaryTree.hpp"
#include "Problem/CountOff.hpp"
#include "Problem/N_Queen.hpp"
#include <cassert>
#include <stdexcept>

int main(int argc, char** argv) {
    Test::run_all_test();
    // CountOff_Solution_Generator::Solution();
    // N_Queen::solution(true);

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
}
