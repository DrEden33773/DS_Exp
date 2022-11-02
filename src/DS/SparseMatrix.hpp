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
#include <array>
#include <concepts>
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
    ElementInfo(const ElementInfo& copied)
        : Row(copied.Row)
        , Col(copied.Col)
        , Value(copied.Value) { }
    ElementInfo(ElementInfo&& moved) noexcept
        : Row(std::move(moved.Row))
        , Col(std::move(moved.Col))
        , Value(std::move(moved.Value)) {
        moved.Row = 0;
        moved.Col = 0;
    }
    ElementInfo& operator=(const ElementInfo& copied) {
        if (&copied == this) {
            return *this;
        }
        Row   = copied.Row;
        Col   = copied.Col;
        Value = copied.Value;
        return *this;
    }
    ElementInfo& operator=(ElementInfo&& moved) noexcept {
        Row       = moved.Row;
        Col       = moved.Col;
        Value     = std::move(moved.Value);
        moved.Row = 0;
        moved.Col = 0;
        return *this;
    }

    /// @brief @b operator==
    friend bool operator==(const ElementInfo<T>& lhs, const ElementInfo<T>& rhs)
    requires std::equality_comparable<T>
    {
        bool if_row_same   = lhs.Row == rhs.Row;
        bool if_col_same   = lhs.Col == rhs.Col;
        bool if_value_same = lhs.Value == rhs.Value;
        return if_col_same && if_row_same && if_value_same;
    }

    /// @brief @b swap_row_and_col
    void swap() {
        std::swap(Row, Col);
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
    explicit SparseMatrix(const std::vector<std::vector<T>>& init) {
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

    SparseMatrix(SparseMatrix& copied)
        : Sizeof_Row(copied.Sizeof_Row)
        , Sizeof_Col(copied.Sizeof_Col)
        , Data(copied.Data) {
    }
    SparseMatrix(SparseMatrix&& moved) noexcept
        : Sizeof_Row(moved.Sizeof_Row)
        , Sizeof_Col(moved.Sizeof_Col)
        , Data(std::move(moved.Data)) {
        moved.Sizeof_Row = 0;
        moved.Sizeof_Col = 0;
        moved.Data       = std::vector<ElementInfo<T>>();
    }

    /// @brief fast_transpose
    SparseMatrix<T> fast_transpose() {
        SparseMatrix<T> res;
        res.Sizeof_Col = Sizeof_Row;
        res.Sizeof_Row = Sizeof_Col;
        res.Data       = std::vector<ElementInfo<T>>(Data.size());

        // nums of col (index = new_row, starts from 1)
        std::vector<int> nums_table(Sizeof_Col + 1, 0);
        // start location (index = new_row, starts from 1)
        std::vector<int> location_table(Sizeof_Col + 1, 0);

        for (int index = 0; index < Data.size(); ++index) {
            ++nums_table[Data[index].Col];
        }
        location_table[1] = 0; // location index starts from zero
        for (int col_index = 2; col_index < Sizeof_Col + 1; ++col_index) {
            location_table[col_index]
                = location_table[col_index - 1] + nums_table[col_index - 1];
        }

        for (int data_index = 0; data_index < Data.size(); ++data_index) {
            int origin_col_index = Data[data_index].Col;
            int curr_index       = location_table[origin_col_index];

            res.Data[curr_index] = Data[data_index];
            res.Data[curr_index].swap();

            ++location_table[origin_col_index]; // need to update start location
        }

        return res;
    }
    SparseMatrix<T> modern_fast_transpose() {
        SparseMatrix<T> res;
        res.Sizeof_Col = Sizeof_Row;
        res.Sizeof_Row = Sizeof_Col;
        res.Data       = std::vector<ElementInfo<T>>(Data.size());

        // { col_index: <nums, start_location> }
        std::unordered_map<int, int> nums_table;
        std::unordered_map<int, int> location_table;

        for (auto&& curr_info : Data) {
            int curr_col = curr_info.Col;
            ++nums_table[curr_col];
        }

        location_table[1] = 0; // location index starts from zero
        for (int col_index = 2; col_index < Sizeof_Col + 1; ++col_index) {
            location_table[col_index]
                = location_table[col_index - 1] + nums_table[col_index - 1];
        }

        for (auto&& origin_info : Data) {
            int origin_col_index = origin_info.Col;
            int curr_index       = location_table[origin_col_index];

            res.Data[curr_index] = origin_info;
            res.Data[curr_index].swap();

            ++location_table[origin_col_index]; // need to update start location
        }

        return res;
    }

    /// @brief @b operator==
    friend bool operator==(const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs)
    requires std::equality_comparable<T>
    {
        bool if_row_same  = lhs.Sizeof_Row == rhs.Sizeof_Row;
        bool if_col_same  = lhs.Sizeof_Col == rhs.Sizeof_Col;
        bool if_data_same = lhs.Data == rhs.Data;
        return if_row_same && if_col_same && if_data_same;
    }
};

} // namespace DS