/**
 * @file SaddlePoint.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief MaAn Point (TextBook T69 P7)
 * @version 0.1
 * @date 2022-10-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <initializer_list>
#include <iostream>
#include <vector>

class SaddlePoint {
    std::vector<std::vector<int>> Data;

    int Row = 0;
    int Col = 0;

public:
    SaddlePoint(std::initializer_list<
                std::initializer_list<int>>&& init) {
        // TODO(eden):
    }
};