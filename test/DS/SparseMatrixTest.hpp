/**
 * @file SparseMatrixTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief SparseMatrixTest
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../src/DS/SparseMatrix.hpp"
#include "../../tools/TestTool.hpp"
#include <cassert>
#include <vector>

namespace Test {

void SparseMatrixTest() {
    Tool::title_info("Sparse_Matrix");

    std::vector<std::vector<int>> init = {
        { 0, 1, 0, 0 },
        { 1, 3, 0, 0 },
        { 0, 0, 0, 4 },
    };

    DS::SparseMatrix<int> origin(init);
    DS::SparseMatrix<int> tr1 = origin.modern_fast_transpose();
    DS::SparseMatrix<int> tr2 = tr1.fast_transpose();

    assert(origin == tr2);

    std::vector<std::vector<int>> empty_init = {
        {}
    };

    DS::SparseMatrix<int> empty_origin(init);
    DS::SparseMatrix<int> empty_tr1 = empty_origin.fast_transpose();
    DS::SparseMatrix<int> empty_tr2 = empty_tr1.modern_fast_transpose();

    assert(empty_origin == empty_tr2);

    std::cout << "Original -> FirstTransposed -> SecondTransposed" << std::endl;
    std::cout << std::endl;

    std::cout << "Original == SecondTransposed" << std::endl;
    std::cout << std::endl;

    std::cout << "Empty and NonEmpty SparseMatrix have all been tested!" << std::endl;
    std::cout << std::endl;

    std::cout << "Transpose is successful!" << std::endl;
    std::cout << std::endl;

    Tool::end_info("Sparse_Matrix");
}

} // namespace Test