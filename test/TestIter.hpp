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

#include "Algorithm/DijkstraTest.hpp"
#include "Algorithm/FloydTest.hpp"
#include "Algorithm/MergeUniqueTest.hpp"
#include "Algorithm/PrimTest.hpp"
#include "DS/BinaryTreeTest.hpp"
#include "DS/DoubleListTest.hpp"
#include "DS/DynamicArrayTest.hpp"
#include "DS/HuffmanTreeTest.hpp"
#include "DS/ListTest.hpp"
#include "DS/QueueTest.hpp"
#include "DS/SingleListTest.hpp"
#include "DS/SparseMatrixTest.hpp"
#include "DS/StackTest.hpp"
#include "DS/UndirectedGraphTest.hpp"

#include <functional>
#include <vector>

namespace Test {

void run_all_test() {
    std::vector<std::function<void()>> test_list = {
        DynamicArrayTest,    // success
        SingleListTest,      // success
        DoubleListTest,      // success
        ListTest,            // success
        MergeUniqueTest,     // success
        SeqStackTest,        // success
        ChainedQueueTest,    // success
        SparseMatrixTest,    // success
        BinaryTreeTest,      // success, but not complete
        UndirectedGraphTest, // success, but not complete
        HuffmanTreeTest,     // success, but not complete
        DijkstraTest,        // success
        FloydTest,
        PrimTest,
    };
    for (auto&& func : test_list) {
        func();
    }
}

} // namespace Test