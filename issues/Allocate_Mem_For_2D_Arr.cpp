/**
 * @file Allocate_Mem_For_2D_Arr.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstddef>
#include <cstdlib>

int** C_Style_Allocate(int row, int col) {
    int** row_ptr = nullptr;
    int*  cow_ptr = nullptr;

    row_ptr = (int**)malloc(row * sizeof(int*));
    for (int row_index = 0; row_index < row; ++row_index) {
        int* cow_ptr = row_ptr[row_index];
        cow_ptr      = (int*)malloc(col * sizeof(int));
    }

    return row_ptr;
}

int** Cpp_Style_Allocate(int row, int col) {
    int** row_ptr = nullptr;
    int*  cow_ptr = nullptr;

    row_ptr = new int*[row];
    for (int row_index = 0; row_index < row; ++row_index) {
        int* cow_ptr = row_ptr[row_index];
        cow_ptr      = new int[col];
    }

    return row_ptr;
}