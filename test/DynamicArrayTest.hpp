/**
 * @file DynamicArrayTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief DynamicArrayTest
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../src/DS/DynamicArray.hpp"

namespace Test {

void DynamicArrayTest() {
    std::cout << std::endl;
    std::cout << "Test Basic Function of the `DynamicArray`. " << std::endl;
    std::cout << std::endl;

    DS::DynamicArray<int> test = { 1, 2, 5, 9, 1, 2 };

    DS::DynamicArray<int> static_created
        = DS::DynamicArray<int>::CreateDynamicArray(
            { 1, 2, 5, 9, 1, 2 }
        );

    test.echo();
    test.std_sort();
    test.echo();

    static_created.echo();
    static_created.std_sort();
    static_created.echo();

    std::cout << std::endl;
    std::cout << "Test of `DynamicArray` is ended. " << std::endl;
    std::cout << std::endl;
}

} // namespace Test