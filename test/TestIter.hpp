/**
 * @file TestIter.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief An Iterator to call all the test with clear information
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "Algorithm/MergeUniqueTest.hpp"
#include "DS/BinaryTreeTest.hpp"
#include "DS/DoubleListTest.hpp"
#include "DS/DynamicArrayTest.hpp"
#include "DS/ListTest.hpp"
#include "DS/QueueTest.hpp"
#include "DS/SingleListTest.hpp"
#include "DS/SparseMatrixTest.hpp"
#include "DS/StackTest.hpp"
#include <functional>

namespace Test {

void run_all_test() {
    std::vector<std::function<void()>> test_list = {
        DynamicArrayTest, // success
        SingleListTest,   // success
        DoubleListTest,   // success
        ListTest,         // success
        MergeUniqueTest,  // success
        SeqStackTest,     // success
        ChainedQueueTest, // success
        SparseMatrixTest, // success
        BinaryTreeTest,
    };
    for (auto&& func : test_list) {
        func();
    }
}

} // namespace Test