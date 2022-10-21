/**
 * @file SparseMatrix.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief SparseMatrix
 * @version 0.1
 * @date 2022-10-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <initializer_list>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace DS {

template <typename T>
struct ElementInfo {
    int Row = 1; // start from 1
    int Col = 1; // start from 1
    T   Value;

    ElementInfo() = default;
    constexpr ElementInfo(int Row, int Col, const T& Value)
        : Row(Row)
        , Col(Col)
        , Value(Value) { }
    ElementInfo(const ElementInfo& copied) {
        Row   = copied.Row;
        Col   = copied.Col;
        Value = copied.Value;
    }
    ElementInfo(ElementInfo&& copied) noexcept {
        Row   = copied.Row;
        Col   = copied.Col;
        Value = std::move(copied.Value);
    }
    ElementInfo& operator=(const ElementInfo& copied) {
        Row   = copied.Row;
        Col   = copied.Col;
        Value = copied.Value;
        return *this;
    }
    ElementInfo& operator=(ElementInfo&& copied) noexcept {
        Row   = copied.Row;
        Col   = copied.Col;
        Value = std::move(copied.Value);
        return *this;
    }
};

template <typename T>
class SparseMatrix {
    int Sizeof_Row = 1; // default = 1
    int Sizeof_Col = 1; // default = 1

    std::vector<ElementInfo<T>> Data = {}; // init with zero mat

public:
    /// @brief constructor & destructor
    constexpr ~SparseMatrix() = default;
    constexpr SparseMatrix()  = default;
    explicit SparseMatrix(std::vector<std::vector<T>>&& init) {
        if (!init.size()) {
            return;
        }
        int init_row = init.size();
        int init_col = init[0].size();
        Sizeof_Row   = init_row;
        Sizeof_Col   = init_col;
        for (int row_index = 0; row_index < init_row; ++row_index) {
            for (int col_index = 0; col_index < init_col; ++col_index) {
                if (auto&& curr = init[row_index][col_index]; curr != 0) {
                    ElementInfo<T> input = {
                        row_index + 1,
                        col_index + 1,
                        init[row_index][col_index]
                    };
                    Data.push_back(input);
                }
            }
        }
    }
    SparseMatrix(std::initializer_list<
                 std::initializer_list<T>>&& init) {
        if (!init.size()) {
            return;
        }
        int init_row = init.size();
        int init_col = init[0].size();
        Sizeof_Row   = init_row;
        Sizeof_Col   = init_col;
        for (int row_index = 0; row_index < init_row; ++row_index) {
            for (int col_index = 0; col_index < init_col; ++col_index) {
                if (init[row_index][col_index]) {
                    ElementInfo<T> input = {
                        row_index + 1,
                        col_index + 1,
                        init[row_index][col_index]
                    };
                    Data.push_back(input);
                }
            }
        }
    }
    SparseMatrix(const SparseMatrix& input) {
        Sizeof_Row = input.Sizeof_Row;
        Sizeof_Col = input.Sizeof_Col;
        Data       = input.Data;
    }
    SparseMatrix(SparseMatrix&& input) noexcept {
        Sizeof_Row = input.Sizeof_Row;
        Sizeof_Col = input.Sizeof_Col;
        Data       = std::move(input.Data);
    }

    /// @brief fast_transpose
    SparseMatrix<T> fast_transpose() {
        SparseMatrix<T> res;
        res.Sizeof_Col = Sizeof_Row;
        res.Sizeof_Row = Sizeof_Col;
        res.Data.reserve(Data.size());

        // nums of col
        int* nums_hashtable = new int[Sizeof_Col + 1]; // index starts from 1
        // start location
        int* location_hashtable = new int[Sizeof_Col + 1]; // index starts from 1

        for (int index = 0; index < Sizeof_Col + 1; ++index) {
            nums_hashtable[index]     = 0;
            location_hashtable[index] = 0;
        }
        for (int index = 0; index < Data.size(); ++index) {
            ++nums_hashtable[Data[index].col];
        }
        location_hashtable[1] = 0; // location index starts from zero
        for (int col_index = 2; col_index < Sizeof_Col + 1; ++col_index) {
            location_hashtable[col_index]
                = location_hashtable[col_index - 1] + nums_hashtable[col_index - 1];
        }

        for (int data_index = 0; data_index < Data.size(); ++data_index) {
            int curr_col_index = Data[data_index].Col;
            int tr_data_index  = location_hashtable[curr_col_index];
            ++location_hashtable[curr_col_index]; // need to update start location
            res[tr_data_index] = Data[curr_col_index];
        }

        return res;
    }
    SparseMatrix<T> modern_fast_transpose() {
        SparseMatrix<T> res;
        res.Sizeof_Col = Sizeof_Row;
        res.Sizeof_Row = Sizeof_Col;
        res.Data.reserve(Data.size());

        // { col_index: <nums, start_location> }
        std::unordered_map<int, int> nums_hashtable;
        std::unordered_map<int, int> location_hashtable;
        for (auto&& curr_info : Data) {
            int curr_col                 = curr_info.Col;
            nums_hashtable[curr_col]     = 0;
            location_hashtable[curr_col] = 0;
        }
        for (auto&& curr_info : Data) {
            int curr_col = curr_info.Col;
            ++nums_hashtable[curr_col];
        }
        location_hashtable[1] = 0; // location index starts from zero
        for (int col_index = 2; col_index < Sizeof_Col + 1; ++col_index) {
            location_hashtable[col_index]
                = location_hashtable[col_index - 1] + nums_hashtable[col_index - 1];
        }

        for (auto&& curr_info : Data) {
            int curr_col_index = curr_info.Col;
            int tr_data_index  = location_hashtable[curr_col_index];
            ++location_hashtable[curr_col_index]; // need to update start location
            res[tr_data_index] = Data[curr_col_index];
        }

        return res;
    }
};

} // namespace DS