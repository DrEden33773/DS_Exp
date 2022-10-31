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

int main(int argc, char** argv) {
    Test::run_all_test();
    // CountOff_Solution_Generator::Solution();
    // N_Queen::solution(true);

    DS::BinaryTree<int> test;
}
