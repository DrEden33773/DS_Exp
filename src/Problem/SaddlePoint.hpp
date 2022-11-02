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

    // { row_index : min_number }
    // row_index => [0, Sizeof_Row)
    std::unordered_map<int, int> min_in_row;
    // { col_index : max_number }
    // col_index => [0, Sizeof_Col)
    std::unordered_map<int, int> max_in_col;

    // location_of_SaddlePoint
    // { row, col }
    // row => [1, Sizeof_Row]
    // col => [1, Sizeof_Col]
    std::vector<std::pair<int, int>> location;

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
        // 1. Init two tables
        // min_in_row => Data[all in 0..Sizeof_Row][0]
        // max_in_col => Data[0][all in 0..Sizeof_Col]
        for (int row_idx = 0; row_idx < Sizeof_Row; ++row_idx) {
            min_in_row[row_idx] = Data[row_idx][0];
        }
        for (int col_idx = 0; col_idx < Sizeof_Col; ++col_idx) {
            max_in_col[col_idx] = Data[0][col_idx];
        }
        // 2. Traverse & Update
        for (int row_idx = 0; row_idx < Sizeof_Row; ++row_idx) {
            for (int col_idx = 0; col_idx < Sizeof_Col; ++col_idx) {
                int curr_elem       = Data[row_idx][col_idx];
                min_in_row[row_idx] = std::min(min_in_row[row_idx], curr_elem);
                max_in_col[col_idx] = std::max(max_in_col[col_idx], curr_elem);
            }
        }
        // 3. select
        for (int row_idx = 0; row_idx < Sizeof_Row; ++row_idx) {
            for (int col_idx = 0; col_idx < Sizeof_Col; ++col_idx) {
                if (min_in_row[row_idx] == max_in_col[col_idx]) {
                    int row = row_idx + 1;
                    int col = col_idx + 1;
                    location.push_back(std::make_pair(row, col));
                }
            }
        }
    }
    void output() {
        if (location.empty()) {
            std::cout << "There's NO SaddlePoint! " << std::endl;
        } else {
            std::cout << "SaddlePoints are => " << std::endl;
            for (auto&& pair : location) {
                std::cout << "(" << pair.first << ", " << pair.second << ")";
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    static void solution(const std::vector<std::vector<int>>& init) {
        SaddlePoint TheSolution(init);
        TheSolution.process();
        TheSolution.output();
    }
    static void TestInterface() {
        std::vector<std::vector<int>> test_with_saddle_point = {
            { 10, 9, 2 },
            { 8, 7, 1 },
            { 5, 4, 3 },
        };
        std::vector<std::vector<int>> test_without_saddle_point = {
            { 10, 9, 2 },
            { 8, 7, 1 },
            { 5, 4, 100 },
        };

        solution(test_with_saddle_point);
        solution(test_without_saddle_point);
    }
};