/**
 * @file ChildSiblingTreeTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../src/DS/ChildSiblingTree.hpp"
#include "../../tools/TestTool.hpp"
#include <string>
#include <vector>

namespace Test {

void ChildSiblingTreeTest() {
    Tool::title_info("Child_Sibling_Tree");

    using std::string;
    using std::vector;

    vector<string> member_list {
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
    };

    DS::ChildSiblingTree<string> Tree(member_list);

    Tree.set_ancestor("A");
    Tree.set_child_of("A", { "B", "C" });
    Tree.set_child_of("B", { "D", "E" });
    Tree.set_child_of("C", { "F", "G" });
    Tree.set_child_of("F", { "H", "I" });

    Tree.debug_print_tree();

    Tree.print_layer(1);
    Tree.print_layer(2);
    Tree.print_layer(3);
    Tree.print_layer(4);

    Tool::end_info("Child_Sibling_Tree");
}

} // namespace Test