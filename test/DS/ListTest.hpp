/**
 * @file ListTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief ListTest (New `double directed` list)
 * @version 0.1
 * @date 2022-10-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../src/DS/List.hpp"
#include "../../tools/TestTool.hpp"

namespace Test {

void ListTest() {
    Tool::title_info("List");

    DS::List<int> static_generated
        = DS::List<int>::CreateList(
            { 1, 2, 5, 9, 1, 2 }
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
    int POS   = static_generated.locate_elem(5);
    int index = POS - 1;
    std::cout << "To locate elem 5 => ";
    std::cout << "POS: " << POS << ", ";
    std::cout << "Index: " << index << ". ";
    std::cout << std::endl;
    std::cout << std::endl;

    Tool::end_info("List");
}

} // namespace Test