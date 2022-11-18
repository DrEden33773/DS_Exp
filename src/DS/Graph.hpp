/**
 * @file Graph.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Directed/Undirected, Weighted/Unweighted, All-in-one
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

// Adj Table => Storage Core

#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Algo {

template <typename T>
class Dijkstra;
template <typename T>
class Floyd;
template <typename T>
class Kruskal;
template <typename T>
class Prim;

} // namespace Algo

namespace DS {

template <class T>
concept Printable = requires(T a) {
    { std::ostream() << a };
};

struct Integer {
    int  value          = 0;
    bool upper_lim_flag = false;
    bool lower_lim_flag = false;
    explicit Integer(int value)
        : value(value) { }
    bool operator==(const Integer& another) {
        bool res = false;

        bool if_this_upper_lim    = this->upper_lim_flag;
        bool if_this_lower_lim    = this->lower_lim_flag;
        bool if_another_upper_lim = another.upper_lim_flag;
        bool if_another_lower_lim = another.lower_lim_flag;
        bool if_this_lim          = if_this_lower_lim && if_this_upper_lim;
        bool if_another_lim       = if_another_lower_lim && if_another_upper_lim;

        if (!if_this_lim && !if_another_lim) {
            res = value == another.value;
        } else {
            if (if_this_upper_lim && if_another_upper_lim) {
                res = true;
            }
            if (if_this_lower_lim && if_another_lower_lim) {
                res = true;
            }
        }

        return res;
    }
    bool operator!=(const Integer& another) {
        return !(*this == another);
    }
    bool operator>(const Integer& another) {
        bool res = true;

        bool if_this_upper_lim    = this->upper_lim_flag;
        bool if_this_lower_lim    = this->lower_lim_flag;
        bool if_another_upper_lim = another.upper_lim_flag;
        bool if_another_lower_lim = another.lower_lim_flag;
        bool if_this_lim          = if_this_lower_lim && if_this_upper_lim;
        bool if_another_lim       = if_another_lower_lim && if_another_upper_lim;

        if (!if_this_lim && !if_another_lim) {
            return this->value > another.value;
        } else {
            if (if_another_upper_lim) {
                res = false;
            }
        }

        return res;
    }
    bool operator<(const Integer& another) {
        return !(*this > another);
    }
    bool operator>=(const Integer& another) {
        return (*this > another) || (*this == another);
    }
    bool operator<=(const Integer& another) {
        return (*this < another) || (*this == another);
    }
};

template <typename T>
requires Printable<T>
class Graph {
    friend class Algo::Dijkstra<T>;
    friend class Algo::Floyd<T>;
    friend class Algo::Kruskal<T>;
    friend class Algo::Prim<T>;

public:
    using MatType    = std::vector<std::vector<int>>;
    using MatRowType = std::vector<int>;

    using EdgeList         = std::vector<std::pair<T, T>>;
    using WeightedEdgeList = std::vector<std::tuple<T, T, int>>;
    using WEdgeList        = std::vector<std::tuple<T, T, int>>;
    using VertexList       = std::vector<T>;

    // static constexpr int LIM = std::numeric_limits<int>::max();
    static constexpr int LIM = -1; // This won't cause overflow!

private:
    std::vector<std::vector<int>> Mat;
    std::unordered_map<T, int>    V_Index_Map;
    std::unordered_map<int, T>    Index_V_Map;

    int  size        = 0;
    bool if_directed = false;
    bool if_weighted = false;

    Graph() = default;
    void copy_from(const Graph& copied) {
        Mat         = copied.Mat;
        V_Index_Map = copied.V_Index_Map;
        Index_V_Map = copied.Index_V_Map;
        size        = copied.size;
        if_directed = copied.if_directed;
        if_weighted = copied.if_weighted;
    }
    void move_from(Graph& moved) {
        Mat         = std::move(moved.Mat);
        V_Index_Map = std::move(moved.V_Index_Map);
        Index_V_Map = std::move(moved.Index_V_Map);
        size        = std::move(moved.size);
        if_directed = std::move(moved.if_directed);
        if_weighted = std::move(moved.if_weighted);
    }
    void init_mat(const int& the_size) {
        int value = (if_weighted) ? LIM : 0;
        Mat       = MatType(the_size, MatRowType(the_size, value));
        if (if_weighted) {
            for (int idx = 0; idx < size; ++idx) {
                Mat[idx][idx] = 0;
            }
        }
    }

public:
    ~Graph() = default;
    Graph(const Graph& copied) {
        copy_from(copied);
    }
    Graph& operator=(const Graph& copied) {
        if (&copied == this) {
            return *this;
        }
        copy_from(copied);
        return *this;
    }
    Graph(Graph&& moved) noexcept {
        move_from(moved);
    }
    Graph& operator=(Graph&& moved) noexcept {
        move_from(moved);
        return *this;
    }

public:
    template <class Edge>
    requires std::is_same_v<Edge, EdgeList> or std::is_same_v<Edge, WEdgeList>
    constexpr Graph(
        const VertexList& VexInit,
        const Edge&       EdgeInit,
        const bool&       if_directed = false
    ) {
        this->if_directed = if_directed;
        if constexpr (std::is_same_v<Edge, WEdgeList>) {
            this->if_weighted = true;
        }
        // 1. import vertex
        const int& num_of_v = VexInit.size();
        size                = num_of_v;
        int curr_idx        = 0;
        for (auto&& curr_vex : VexInit) {
            V_Index_Map[curr_vex] = curr_idx;
            Index_V_Map[curr_idx] = curr_vex;
            ++curr_idx;
        }
        // 2. init Mat
        init_mat(size);
        // 3. add edges
        if constexpr (std::is_same_v<Edge, WEdgeList>) {
            for (auto&& [a_vex, b_vex, weight] : EdgeInit) {
                InsertArc(a_vex, b_vex, weight);
            }
        } else {
            for (auto&& [a_vex, b_vex] : EdgeInit) {
                InsertArc(a_vex, b_vex);
            }
        }
    }

public:
    /// @brief @b vex_opt
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
    void make_sure_has_vex(const T& v_name) {
        if (!V_Index_Map.contains(v_name)) {
            throw std::logic_error("Undirected graph doesn't contain all of input vertexes!");
        }
    }
    void make_sure_has_index(const int& index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Input `index` is out of range!");
        }
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
    void InsertVex(const T& NewVex) {
        if (if_has_vex(NewVex)) {
            std::cout << "Already have the input vertex, escape insertion... " << std::endl;
            return;
        }
        // 1. update map
        const int& curr_inserted_idx   = size;
        V_Index_Map[NewVex]            = curr_inserted_idx;
        Index_V_Map[curr_inserted_idx] = NewVex;
        // 2. update size
        ++size;
        // 3. update Mat
        Mat.resize(size);
        int value = (if_weighted) ? LIM : 0;
        for (std::vector<int>& row_vec : Mat) {
            row_vec.push_back(value);
        }
        auto&& new_row = std::vector<int>(size, value);
        Mat.emplace_back(new_row);
    }
    void DeleteVex(const T& DelVex) {
        if (!if_has_vex(DelVex)) {
            throw std::logic_error("Input Vertex is NOT exist!");
            // return;
        }
        int DelIdx = V_Index_Map[DelVex];

        MatType    NewMat;
        MatRowType TempRow;
        NewMat.reserve(size);
        TempRow.reserve(size);
        for (int row_idx = 0; row_idx < size; ++row_idx) {
            if (row_idx == DelIdx) {
                continue;
            }
            for (int col_idx = 0; col_idx < size; ++col_idx) {
                if (col_idx == DelIdx) {
                    continue;
                }
                TempRow.emplace_back(Mat[row_idx][col_idx]);
            }
            NewMat.emplace_back(TempRow);
            TempRow.clear();
        }

        Mat = std::move(NewMat);
    }
    /// @brief @b arc_opt
    void ArcOpt(
        const T&    from_vex,
        const T&    to_vex,
        const bool& if_delete = false,
        const int&  weight    = 0
    ) {
        if (!if_has_vex(from_vex) || !if_has_vex(to_vex)) {
            throw std::logic_error("Undirected graph doesn't contain all of input vertexes!");
        }
        int from_idx = V_Index_Map[from_vex];
        int to_idx   = V_Index_Map[to_vex];
        if (!if_weighted) {
            Mat[from_idx][to_idx] = (if_delete) ? 0 : 1;
            if (!if_directed) {
                Mat[to_idx][from_idx] = (if_delete) ? 0 : 1;
            }
        } else {
            Mat[from_idx][to_idx] = (if_delete) ? LIM : weight;
            if (!if_directed) {
                Mat[to_idx][from_idx] = (if_delete) ? LIM : weight;
            }
        }
    }
    void InsertArc(
        const T&   from_vex,
        const T&   to_vex,
        const int& weight = 0
    ) {
        ArcOpt(from_vex, to_vex, false, weight);
    }
    void DeleteArc(
        const T&   from_vex,
        const T&   to_vex,
        const int& weight = 0
    ) {
        ArcOpt(from_vex, to_vex, true, weight);
    }

public:
    void make_sure_weighted() {
        if (!if_weighted) {
            throw std::logic_error("This function requires a `Weighted_Graph`!");
        }
    }
    void make_sure_undirected() {
        if (if_directed) {
            throw std::logic_error("This function requires a `Undirected_Graph`!");
        }
    }
    void make_sure_non_empty() {
        if (!size) {
            throw std::logic_error("This function requires a `NonEmpty_Graph`!");
        }
    }
    int get_low_cost_of(const T& a_vex, const T& b_vex) {
        make_sure_weighted();
        make_sure_has_vex(a_vex);
        make_sure_has_vex(b_vex);
        const int& a_idx = V_Index_Map[a_vex];
        const int& b_idx = V_Index_Map[b_vex];
        return Mat[a_idx][b_idx]; //==> LIM / 0 / weight
    }
};

} // namespace DS