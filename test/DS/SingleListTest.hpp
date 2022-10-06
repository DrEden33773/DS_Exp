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

#pragma once
#include "../../src/DS/LinkedList/SingleList.hpp"

namespace Test {

void SingleListTest() {
    std::cout << std::endl;
    std::cout << "Test Basic Function of the `SingleList`. " << std::endl;
    std::cout << std::endl;

    DS::SingleList<int> test = { 1, 5, 9, 2, 7, 4, 9, 0, 1 };

    test.echo();
    test.reverse();
    test.echo();

    DS::SingleList<int> static_generated
        = DS::SingleList<int>::CreateSingleList(
            { 1, 5, 9, 2, 7, 4, 9, 0, 1 }
        );

    static_generated.echo();
    static_generated.reverse();
    static_generated.echo();

    std::cout << std::endl;
    std::cout << "Test of `SingleList` is ended. " << std::endl;
    std::cout << std::endl;
}

} // namespace Test