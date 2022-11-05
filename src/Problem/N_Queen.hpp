/**
 * @file N_Queen.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief N_Queen
 * @version 0.1
 * @date 2022-10-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

class N_Queen {
public:
    /// @brief index = row, value = col
    std::vector<int> queens;

    /// @brief already_in cols
    std::unordered_set<int> cols;

    /// @brief already_in main_diagonals
    std::unordered_set<int> main_diags;

    /// @brief already_in sub_diagonals
    std::unordered_set<int> sub_diags;

    /// @brief solution
    std::vector<std::vector<std::string>> solutions;

    std::vector<std::vector<std::string>> solveNQueen(int n) {
        queens     = std::vector<int>(n, -1); // default col = -1
        cols       = std::unordered_set<int>(n);
        main_diags = std::unordered_set<int>(n);
        sub_diags  = std::unordered_set<int>(n);
        solutions  = std::vector<std::vector<std::string>>();

        // back_trace(n, 0);
        fastest_back_trace(n);

        return solutions;
    }

    /// @brief @b Recursive_Implementation
    void back_trace(const int& row_lim, const int& row = 0) {
        if (row == row_lim) {
            auto&& board = gen_a_board(row_lim);
            solutions.push_back(board);
        } else {
            for (int col = 0; col < row_lim; ++col) {
                // 1. detect if_conflict
                if (cols.find(col) != cols.end()) {
                    continue;
                }
                int main_diag = col - row;
                if (main_diags.find(main_diag) != main_diags.end()) {
                    continue;
                }
                int sub_diag = col + row;
                if (sub_diags.find(sub_diag) != sub_diags.end()) {
                    continue;
                } // could found no conflict position

                // 2. add location info
                queens[row] = col;
                cols.insert(col);
                main_diags.insert(main_diag);
                sub_diags.insert(sub_diag);

                // 3. recurse to the next row
                back_trace(row_lim, row + 1);

                // If come to next board, there're two cases:
                // (1). `back_trace` before arrives `row_lim`
                // (2). `back_trace` before cannot find non-conflict place
                // In any case, you should clear curr_info
                // for iterate to a new `col_index`

                // 3. clear information
                queens[row] = -1;
                cols.erase(col);
                main_diags.erase(main_diag);
                sub_diags.erase(sub_diag);
            }
        }
    }

    /// @brief @b Iterative_Implementation
    void fastest_back_trace(const int& row_lim) {
        std::stack<int> stack_of_row;
        std::stack<int> stack_of_col;

        int  row                     = 0;
        bool if_prev_conflict        = false;
        bool if_just_find_a_solution = false;
        int  prev_col                = 0;
        do {
            if (row == row_lim) {
                auto&& board = gen_a_board(row_lim);
                solutions.push_back(board);

                prev_col = stack_of_col.top();
                stack_of_row.pop();
                stack_of_col.pop();
                --row;

                if_just_find_a_solution = true;
            } else {
                if (!if_prev_conflict) {
                    stack_of_row.push(row);
                    if (!if_just_find_a_solution) {
                        stack_of_col.push(0);
                    } else {
                        stack_of_col.push(prev_col + 1);
                        // clear prev_info
                        queens[row] = -1;
                        cols.erase(prev_col);
                        main_diags.erase(prev_col - row);
                        sub_diags.erase(prev_col + row);
                        if_just_find_a_solution = false;
                    }
                } else {
                    // clear prev_info
                    queens[row] = -1;
                    cols.erase(prev_col);
                    main_diags.erase(prev_col - row);
                    sub_diags.erase(prev_col + row);
                    if_prev_conflict = false;
                }

                bool if_conflict = true;
                for (int col = stack_of_col.top(); col < row_lim; ++col) {
                    // sync => top <-> col
                    stack_of_col.top() = col;

                    // 1. detect if_conflict
                    if (cols.find(col) != cols.end()) {
                        continue;
                    }
                    int main_diag = col - row;
                    if (main_diags.find(main_diag) != main_diags.end()) {
                        continue;
                    }
                    int sub_diag = col + row;
                    if (sub_diags.find(sub_diag) != sub_diags.end()) {
                        continue;
                    } // could found no conflict position
                    if_conflict = false;

                    // 2. add location info
                    queens[row] = col;
                    cols.insert(col);
                    main_diags.insert(main_diag);
                    sub_diags.insert(sub_diag);

                    // 3. done, go to the next row
                    break;
                }
                if (if_conflict) {
                    stack_of_row.pop();
                    stack_of_col.pop();
                    if (stack_of_row.empty() || stack_of_col.empty()) {
                        break;
                    }
                    prev_col = stack_of_col.top();
                    ++stack_of_col.top();
                    --row; // turn back to prev one
                    if_prev_conflict = true;
                } else {
                    ++row;
                }
            }
        } while (!stack_of_row.empty());
    }

    std::vector<std::string> gen_a_board(const int& n) {
        auto board = std::vector<std::string>();
        board.reserve(n);
        for (int i = 0; i < n; i++) {
            std::string row = std::string(n, '.');
            auto&&      col = queens[i];
            row[col]        = 'Q';
            board.emplace_back(row);
        }
        return board;
    }

    static void solution(bool if_show_graphic_solution = false) {
        N_Queen The_Solution;

        int num_of_queens = 0;
        while (true) {
            std::cout << "Please input the num of queens (>0) => ";
            std::cin >> num_of_queens;
            std::cout << std::endl;
            if (num_of_queens <= 0) {
                std::cout << "Input num should >0, please try again. " << std::endl;
                std::cout << std::endl;
            } else {
                break;
            }
        }

        The_Solution.solveNQueen(num_of_queens);

        std::cout << "There're " << The_Solution.solutions.size() << " solutions. ";
        std::cout << std::endl;
        std::cout << std::endl;

        if (if_show_graphic_solution && The_Solution.solutions.size()) {
            std::cout << "They are => " << std::endl;
            std::cout << std::endl;

            int curr_solution_num = 0;
            for (auto&& board : The_Solution.solutions) {
                ++curr_solution_num;
                std::cout << curr_solution_num << ": " << std::endl;
                for (auto&& row : board) {
                    std::cout << row << std::endl;
                }
                std::cout << std::endl;
            }
        }

        std::cout << "Repeat! ";
        std::cout << "There're " << The_Solution.solutions.size() << " solutions. ";
        std::cout << std::endl;
        std::cout << std::endl;
    }
};
