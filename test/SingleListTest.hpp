/**
 * @file SingleListTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../src/DS/LinkedList/SingleList.hpp"

namespace Test {

void SingleListTest() {
    std::cout << std::endl;
    DS::SingleList<int> test = { 1, 5, 9, 2, 7, 4, 9, 0, 1 };
    test.echo();
}

}