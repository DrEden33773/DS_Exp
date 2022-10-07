/**
 * @file MergeUniqueTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../src/DS/DynamicArray.hpp"
#include "../../src/DS/LinkedList/SingleList.hpp"
#include "../../tools/TestTool.hpp"

namespace Test {

void MergeUniqueTest() {
    Tool::title_info("MergeUnique");

    std::cout << "Single-list First!" << std::endl;
    std::cout << std::endl;

    auto SingleList_A
        = DS::SingleList<int>::CreateSingleList(
            { 1, 5, 2, 9, 4, 0 }
        );
    auto SingleList_B
        = DS::SingleList<int>::CreateSingleList(
            { 7, 10, 3, 9, 4, 0, 1, 3 }
        );
    SingleList_A.echo();
    SingleList_B.echo();

    DS::SingleList<int>::Merge_Unique(SingleList_A, SingleList_B);
    SingleList_A.echo();
    SingleList_B.echo();

    {
        auto SingleList_A
            = DS::SingleList<int>::CreateSingleList(
                {}
            );
        auto SingleList_B
            = DS::SingleList<int>::CreateSingleList(
                {}
            );
        SingleList_A.echo();
        SingleList_B.echo();

        DS::SingleList<int>::Merge_Unique(SingleList_A, SingleList_B);
        SingleList_A.echo();
        SingleList_B.echo();
    }

    Tool::end_info("MergeUnique");
}

} // namespace Test