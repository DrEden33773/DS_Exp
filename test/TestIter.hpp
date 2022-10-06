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
#include "DS/DynamicArrayTest.hpp"
#include "DS/SingleListTest.hpp"
#include <functional>

namespace Test {

void run_all_test() {
    std::vector<std::function<void()>> all_test = {
        DynamicArrayTest,
        SingleListTest,
    };
    for (auto&& func : all_test) {
        func();
    }
}

} // namespace Test