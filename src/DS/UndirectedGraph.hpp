/**
 * @file UndirectedGraph.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief BasicUndirectedGraph (Adjacency Matrix Ver.)
 * @version 0.1
 * @date 2022-11-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
namespace DS {

template <typename T>
class UndirectedGraph {
    using UG         = UndirectedGraph<T>;
    using MatType    = std::vector<std::vector<int>>;
    using MatRowType = std::vector<int>;

private:
    std::vector<std::vector<int>> Mat;
    std::unordered_map<T, int>    V_Index_Map;
    std::unordered_map<int, T>    Index_V_Map;
    int                           size = 0;

    UndirectedGraph() = default;
    void copy_from(const UG& copied) {
        Mat         = copied.Mat;
        V_Index_Map = copied.V_Index_Map;
        Index_V_Map = copied.Index_V_Map;
        size        = copied.size;
    }
    void move_from(UG& moved) {
        Mat         = std::move(moved.Mat);
        V_Index_Map = std::move(moved.V_Index_Map);
        Index_V_Map = std::move(moved.Index_V_Map);
        size        = std::move(moved.size);
    }
    void init_mat(const int& the_size) {
        Mat = MatType(the_size, MatRowType(the_size, 0));
    }

public:
    /// @b destruction
    ~UndirectedGraph() = default;

    /// @b copy_construction
    UndirectedGraph(const UG& copied) {
        copy_from(copied);
    }
    UndirectedGraph& operator=(const UG& copied) {
        if (&copied == this) {
            return *this;
        }
        copy_from(copied);
        return *this;
    }

    /// @b move_construction
    UndirectedGraph(UG&& moved) noexcept {
        move_from(moved);
    }
    UndirectedGraph& operator=(UG&& moved) noexcept {
        move_from(moved);
        return *this;
    }

    /// @b constructor
public:
    using ConstructList = std::vector<std::pair<T, T>>;
    explicit UndirectedGraph(const ConstructList& init) {
        std::unordered_set<T> V_Set;
        int                   num_of_V = 0;
        // 1. build map, get num_of_V
        for (const std::pair<T, T>& V_pair : init) {
            const T& from = V_pair.first;
            const T& to   = V_pair.second;
            if (!V_Set.contains(from)) {
                V_Set.insert(from);
                V_Index_Map[from]     = num_of_V;
                Index_V_Map[num_of_V] = from;
                ++num_of_V;
            }
            if (!V_Set.contains(to)) {
                V_Set.insert(to);
                V_Index_Map[to]       = num_of_V;
                Index_V_Map[num_of_V] = to;
                ++num_of_V;
            }
        }
        size = num_of_V;
        // 2. init Mat
        init_mat(size);
        // 3. build the Mat
        for (const std::pair<T, T>& V_pair : init) {
            int first_idx  = V_Index_Map[V_pair.first];
            int second_idx = V_Index_Map[V_pair.second];
            // set => Mat[][] = 1
            Mat[first_idx][second_idx] = 1;
            Mat[second_idx][first_idx] = 1;
        }
    }

    /// @b vertex_operations
public:
    bool if_has_vex(const T& v_name) {
        if (!V_Index_Map.contains(v_name)) {
            return false;
        }
        return true;
    }
    bool if_has_index(const int& index) {
        if (index < 0 || index >= size) {
            return false;
        }
        return true;
    }

    int GetIndex(const T& v_name) {
        int res = -1;
        if (V_Index_Map.contains(v_name)) {
            res = V_Index_Map[v_name];
        }
        return res;
    }
    T GetVex(const int& index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Input `index` is out of range!");
        }
        return Index_V_Map[index];
    }

    int FindAdjIndex(const int& index) {
        if (!if_has_index(index)) {
            return -1;
        }
        int index_ans = -1;
        for (int col_idx = 0; col_idx < size; ++col_idx) {
            if (Mat[index][col_idx]) {
                index_ans = col_idx;
                break;
            }
        }
        return index_ans;
    }
    int FindAdjIndex(const T& v_name) {
        if (!if_has_vex(v_name)) {
            return -1;
        }
        int idx_of_input = GetIndex(v_name);
        return FindAdjIndex(idx_of_input);
    }
};

} // namespace DS