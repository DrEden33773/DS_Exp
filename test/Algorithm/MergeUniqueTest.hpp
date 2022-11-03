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
#include "../../src/DS/LinkedList/DoubleList.hpp"
#include "../../src/DS/LinkedList/SingleList.hpp"
#include "../../src/DS/List.hpp"
#include "../../tools/TestTool.hpp"

namespace Test {

void SingleList_() {
    std::cout << ">>>>>>>>>> SingleList <<<<<<<<<<" << std::endl;
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

    { // empty list check => succeed!
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
}

void DynamicArray_() {
    std::cout << ">>>>>>>>>> DynamicArray <<<<<<<<<<" << std::endl;
    std::cout << std::endl;

    auto DynamicArray_A
        = DS::DynamicArray<int>::CreateDynamicArray(
            { 1, 5, 2, 9, 4, 0 }
        );
    auto DynamicArray_B
        = DS::DynamicArray<int>::CreateDynamicArray(
            { 7, 10, 3, 9, 4, 0, 1, 3 }
        );
    DynamicArray_A.echo();
    DynamicArray_B.echo();

    DS::DynamicArray<int>::Merge_Unique(DynamicArray_A, DynamicArray_B);
    DynamicArray_A.echo();
    DynamicArray_B.echo();

    { // empty check => success!
        auto DynamicArray_A
            = DS::DynamicArray<int>::CreateDynamicArray(
                {}
            );
        auto DynamicArray_B
            = DS::DynamicArray<int>::CreateDynamicArray(
                {}
            );
        DynamicArray_A.echo();
        DynamicArray_B.echo();

        DS::DynamicArray<int>::Merge_Unique(DynamicArray_A, DynamicArray_B);
        DynamicArray_A.echo();
        DynamicArray_B.echo();
    }
}

void DoubleList_() {
    std::cout << ">>>>>>>>>> DoubleList <<<<<<<<<<" << std::endl;
    std::cout << std::endl;

    auto DoubleList_A
        = DS::DoubleList<int>::CreateDoubleList(
            { 1, 5, 2, 9, 4, 0 }
        );
    auto DoubleList_B
        = DS::DoubleList<int>::CreateDoubleList(
            { 7, 10, 3, 9, 4, 0, 1, 3 }
        );
    DoubleList_A.echo();
    DoubleList_B.echo();

    DS::DoubleList<int>::Merge_Unique(DoubleList_A, DoubleList_B);
    DoubleList_A.echo();
    DoubleList_B.echo();

    { // empty check => success!
        auto DoubleList_A
            = DS::DoubleList<int>::CreateDoubleList(
                {}
            );
        auto DoubleList_B
            = DS::DoubleList<int>::CreateDoubleList(
                {}
            );
        DoubleList_A.echo();
        DoubleList_B.echo();

        DS::DoubleList<int>::Merge_Unique(DoubleList_A, DoubleList_B);
        DoubleList_A.echo();
        DoubleList_B.echo();
    }
}

void List_() {
    std::cout << ">>>>>>>>>> List <<<<<<<<<<" << std::endl;
    std::cout << std::endl;

    DS::List<int> List_A = { 1, 5, 2, 9, 4, 0 };
    DS::List<int> List_B = { 7, 10, 3, 9, 4, 0, 1, 3 };

    List_A.echo();
    List_B.echo();

    DS::List<int>::Merge_Unique(List_A, List_B, false);
    List_A.echo();
    List_B.echo();

    { // empty check
        DS::List<int> List_A = {};
        DS::List<int> List_B = {};

        List_A.echo();
        List_B.echo();

        DS::List<int>::Merge_Unique(List_A, List_B);
        List_A.echo();
        List_B.echo();
    }
}

void MergeUniqueTest() {
    Tool::title_info("MergeUnique");

    SingleList_();
    DynamicArray_();
    DoubleList_();
    List_();

    Tool::end_info("MergeUnique");
}

} // namespace Test