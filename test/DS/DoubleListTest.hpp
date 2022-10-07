/**
 * @file DoubleListTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../src/DS/LinkedList/DoubleList.hpp"
#include "../../tools/TestTool.hpp"

namespace Test {

void DoubleListTest() {
    Tool::title_info("Double_List");

    DS::DoubleList<int> static_generated
        = DS::DoubleList<int>::CreateDoubleList(
            { 1, 4, 2, 9, 10, 9, 8 }
        );

    /// @brief @b echo()
    static_generated.echo();

    /// @brief @b std_sort()
    static_generated.std_sort();
    static_generated.echo();

    Tool::end_info("Double_List");
}

} // namespace Test