/**
 * @file Graph.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Directed/Undirected, Weighted/Unweighted, Aint-in-one
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

namespace DS {

template <typename T>
class Graph {
public:
    using MatType    = std::vector<std::vector<int>>;
    using MatRowType = std::vector<int>;

    using EdgeList         = std::vector<std::pair<T, T>>;
    using WeightedEdgeList = std::vector<std::tuple<T, T, int>>;
    using WEdgeList        = std::vector<std::tuple<T, T, int>>;
    using VertexList       = std::vector<T>;

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
        int value = (if_weighted) ? 0 : -1;
        Mat       = MatType(the_size, MatRowType(the_size, value));
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
    static Graph<T> CreateGraph(
        const VertexList& VexInit,
        const Edge&       EdgeInit,
        const bool&       if_directed = false
    ) {
        Graph<T> ret;
        ret.if_directed = if_directed;
        if constexpr (std::is_same_v<Edge, WEdgeList>) {
            ret.if_weighted = true;
        }
    }
};

} // namespace DS