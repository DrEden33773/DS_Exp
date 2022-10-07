/**
 * @file Merge_Unique_LinkedList.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Give to `descending ordered` LinkedList, then merge and unique the final result
 * @attention S(n) should equal to O(1), and merge_unique it into the former input
 * @version 0.1
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../DS/LinkedList/SingleList.hpp"

namespace Algorithm {

void Merge_Unique_LinkedList(
    DS::SingleList<int>& A, DS::SingleList<int>& B
) {
    // 1. check if_empty
    bool if_A_empty = A.if_empty();
    bool if_B_empty = B.if_empty();
    // 2. make_sure_descending_order
    A.select_sort(); // A ascending_order
    A.reverse();     // A descending_order
    B.select_sort(); // B ascending_order
    B.reverse();     // B descending_order
    // 3. TO OPERATE
}

} // namespace Algorithm