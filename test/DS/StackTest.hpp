/**
 * @file StackTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../src/DS/Stack.hpp"
#include "../../tools/TestTool.hpp"

namespace Test {

void SeqStackTest() {
    Tool::title_info("Sequential_Stack");

    DS::Stack<int> test_1 = { 1, 2, 3, 4, 5 };
    std::cout << test_1.get_back() << std::endl;
    std::cout << test_1.get_length() << std::endl;
    std::cout << std::endl;

    test_1.echo();

    test_1.pop();
    test_1.pop();
    test_1.pop();
    test_1.pop();
    test_1.pop();
    test_1.echo();

    test_1.push(10);
    test_1.push(12);
    test_1.echo();

    DS::Stack<int> test_2 = {};
    test_2.echo();

    test_2.push(10, 11, 13, 14, 18, 2, 5);
    test_2.echo();

    test_2.pop();
    test_2.pop();
    test_2.echo();

    Tool::end_info("Sequential_Stack");
}

} // namespace Test