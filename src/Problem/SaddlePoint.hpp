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

#include <iostream>
#include <unordered_map>
#include <vector>

class SaddlePoint {
    std::vector<std::vector<int>> Data;

    int Sizeof_Row = 0;
    int Sizeof_Col = 0;

    std::unordered_map<int, int> min_in_row;
    std::unordered_map<int, int> max_in_col;

    SaddlePoint() = default;

public:
    explicit SaddlePoint(const std::vector<std::vector<int>>& init)
        : Sizeof_Row(static_cast<int>(init.size()))
        , Sizeof_Col(static_cast<int>(init.begin()->size())) {
        std::vector<int> input_sub;
        Data.reserve(Sizeof_Row);
        input_sub.reserve(Sizeof_Col);
        for (auto&& sub : init) {
            for (auto&& elem : sub) {
                input_sub.emplace_back(elem);
            }
            Data.emplace_back(input_sub);
            input_sub.clear();
        }
    }
    void process() {
    }

    static void solution(const std::vector<std::vector<int>>& init) {
        SaddlePoint TheSolution(init);
    }
};