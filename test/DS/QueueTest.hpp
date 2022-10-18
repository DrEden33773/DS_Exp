/**
 * @file QueueTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../src/DS/Queue.hpp"
#include "../../tools/TestTool.hpp"

namespace Test {

void ChainedQueueTest() {
    Tool::title_info("Chained_Queue");

    DS::Queue<int> test_1 = { 1, 2, 3, 4, 5 };
    std::cout << test_1.get_front() << std::endl;
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

    DS::Queue<int> test_2 = {};
    test_2.echo();

    test_2.push(10, 11, 13, 14, 18, 2, 5);
    test_2.echo();

    test_2.pop();
    test_2.pop();
    test_2.echo();

    Tool::end_info("Chained_Queue");
}

} // namespace Test