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
#include "../../tools/TestTool.hpp"

namespace Test {

void SingleListTest() {
    Tool::title_info("Single_List");

    DS::SingleList<int> static_generated
        = DS::SingleList<int>::CreateSingleList(
            { 1, 5, 9, 2, 7, 4, 9, 0, 1 }
        );
    /// @brief @b echo()
    static_generated.echo();

    /// @brief @b reverse()
    static_generated.reverse();
    static_generated.echo();
    static_generated.reverse();

    /// @brief @b insert_elem()
    static_generated.insert_elem(12, 3);
    static_generated.insert_elem(2, 1);
    // static_generated.insert_elem(12, 0);  // error, throw exception
    // static_generated.insert_elem(12, 10); // error, throw exception
    static_generated.echo();

    /// @brief @b push_back()
    static_generated.push_back(15);
    static_generated.echo();

    /// @brief @b delete_elem()
    static_generated.delete_elem(4);
    static_generated.delete_elem(1);
    // static_generated.delete_elem(0); // error, throw exception
    static_generated.echo();

    /// @brief @b locate_elem()
    int POS   = static_generated.locate_elem(9);
    int index = POS - 1;
    std::cout << "To locate elem 9 => ";
    std::cout << "POS: " << POS << ", ";
    std::cout << "Index: " << index << ". ";
    std::cout << std::endl;
    std::cout << std::endl;

    /// @brief @b unique()
    static_generated.unique(true);  // emplace_unique => O(n^2)
    static_generated.unique(false); // hash_unique => O(n)
    static_generated.echo();        /* shows the outcome of emplace_unique */

    /// @brief @b insert_sort()
    static_generated.select_sort();
    static_generated.echo();

    Tool::end_info("Single_List");
}

} // namespace Test