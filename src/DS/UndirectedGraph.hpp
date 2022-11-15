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

#include <iostream>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace DS {

template <typename T>
class UndirectedGraph {
public:
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
    using ConstructList    = std::vector<std::pair<T, T>>;
    using EdgeList         = std::vector<std::pair<T, T>>;
    using VertexList       = std::vector<T>;
    using WeightedEdgeList = std::vector<std::tuple<T, T, int>>;

    explicit UndirectedGraph(const EdgeList& init) {
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
    explicit UndirectedGraph(
        const VertexList& VexInit,
        const EdgeList&   EdgeInit
    ) {
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
        for (auto&& [a_vex, b_vex] : EdgeInit) {
            InsertArc(a_vex, b_vex);
        }
    }

    /// @b vertex_operations
public:
    bool
    if_has_vex(const T& v_name) {
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
    std::vector<int> FindAllAdjIndex(const int& index) {
        std::vector<int> res;
        if (!if_has_index(index)) {
            return res;
        }
        for (int col_idx = 0; col_idx < size; ++col_idx) {
            if (Mat[index][col_idx]) {
                res.push_back(col_idx);
            }
        }
        return res;
    }
    std::vector<int> FindAllAdjIndex(const T& v_name) {
        std::vector<int> res;
        if (!if_has_vex(v_name)) {
            return res;
        }
        int idx_of_input = GetIndex(v_name);
        return FindAllAdjIndex(idx_of_input);
    }

    /// @b Traverse_And_Search
public:
    using HashSet = std::unordered_set<int>;
    void DFS_Rec_Func(HashSet& visited_idx, const int& idx) {
        // 1. output
        std::cout << Index_V_Map[idx] << " ";
        // 2. add flag
        visited_idx.insert(idx);
        // 3. get all adj_idx
        std::vector<int>&& adj_idx_list = FindAllAdjIndex(idx);
        // 4. step into those unvisited
        for (const int& adj_idx : adj_idx_list) {
            if (!visited_idx.contains(adj_idx)) {
                DFS_Rec_Func(visited_idx, adj_idx);
            }
        }
    }
    /// @b DFS_From_Vex_With_Outer_Set
    void DFS(const T& vex, std::unordered_set<int>& visited_idx) {
        if (!if_has_vex(vex)) {
            throw std::logic_error("Input vertex is NOT exist!");
        }
        if (!size) {
            std::cout << "Empty Undirected Graph... " << std::endl;
            return;
        }
        DFS_Rec_Func(visited_idx, V_Index_Map[vex]);
    }
    /// @b DFS_From_Vex
    void DFS(const T& vex) {
        if (!if_has_vex(vex)) {
            throw std::logic_error("Input vertex is NOT exist!");
        }
        if (!size) {
            std::cout << "Empty Undirected Graph... " << std::endl;
            return;
        }
        std::unordered_set<int> visited_idx;
        DFS_Rec_Func(visited_idx, V_Index_Map[vex]);
    }
    /// @b BFS_From_Vex_With_Outer_Set
    void BFS(const T& vex, std::unordered_set<int>& visited_idx) {
        if (!if_has_vex(vex)) {
            throw std::logic_error("Input vertex is NOT exist!");
        }
        if (!size) {
            std::cout << "Empty Undirected Graph... " << std::endl;
            return;
        }
        std::queue<int> queue;

        queue.push(V_Index_Map[vex]);
        // add `visited_flag` as soon as it joins the queue
        visited_idx.insert(V_Index_Map[vex]);

        while (!queue.empty()) {
            int curr_level_size = static_cast<int>(queue.size());
            for (int i = 0; i < curr_level_size; ++i) {
                // 1. get current_index
                const int& curr_idx = queue.front();
                // 2. output current_vertex
                std::cout << Index_V_Map[curr_idx] << " ";
                // 4. put `all unvisited adj_idx` into the queue
                std::vector<int>&& adj_idx_list = FindAllAdjIndex(curr_idx);
                for (const int& adj_idx : adj_idx_list) {
                    if (!visited_idx.contains(adj_idx)) {
                        queue.push(adj_idx);
                        // add `visited_flag` as soon as it joins the queue
                        visited_idx.insert(adj_idx);
                    }
                }
                // 5. remove curr_idx from queue
                queue.pop();
            }
        }
    }
    /// @b BFS_From_Vex
    void BFS(const T& vex) {
        if (!if_has_vex(vex)) {
            throw std::logic_error("Input vertex is NOT exist!");
        }
        if (!size) {
            std::cout << "Empty Undirected Graph... " << std::endl;
            return;
        }
        std::queue<int>         queue;
        std::unordered_set<int> visited_idx;

        queue.push(V_Index_Map[vex]);
        // add `visited_flag` as soon as it joins the queue
        visited_idx.insert(V_Index_Map[vex]);

        while (!queue.empty()) {
            int curr_level_size = static_cast<int>(queue.size());
            for (int i = 0; i < curr_level_size; ++i) {
                // 1. get current_index
                const int& curr_idx = queue.front();
                // 2. output current_vertex
                std::cout << Index_V_Map[curr_idx] << " ";
                // 4. put `all unvisited adj_idx` into the queue
                std::vector<int>&& adj_idx_list = FindAllAdjIndex(curr_idx);
                for (const int& adj_idx : adj_idx_list) {
                    if (!visited_idx.contains(adj_idx)) {
                        queue.push(adj_idx);
                        // add `visited_flag` as soon as it joins the queue
                        visited_idx.insert(adj_idx);
                    }
                }
                // 5. remove curr_idx from queue
                queue.pop();
            }
        }
    }
    void DFSTraverse() {
        std::unordered_set<int> visited_idx {};
        for (int idx = 0; idx < size; ++idx) {
            if (!visited_idx.contains(idx)) {
                DFS(Index_V_Map[idx], visited_idx);
            }
        }
        std::cout << std::endl;
    }
    void BFSTraverse() {
        std::unordered_set<int> visited_idx {};
        for (int idx = 0; idx < size; ++idx) {
            if (!visited_idx.contains(idx)) {
                BFS(Index_V_Map[idx], visited_idx);
            }
        }
        std::cout << std::endl;
    }
    void EchoVIndexTable() {
        /// @warning @b Only_Working_While_T_Overloaded_<<
        if (!size) {
            std::cout << "Empty Undirected Graph!";
            std::cout << std::endl;
        }
        int curr_idx = 0;
        for (int idx = 0; idx < size; ++idx) {
            std::cout << idx << " <=> " << Index_V_Map[idx];
            std::cout << std::endl;
        }
    }

    /// @b another_operations
public:
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
        for (std::vector<int>& row_vec : Mat) {
            row_vec.push_back(0);
        }
        auto&& new_row = std::vector<int>(size, 0);
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
    void ArcOpt(const T& a_vex, const T& b_vex, bool if_delete = false) {
        if (!if_has_vex(a_vex) || !if_has_vex(b_vex)) {
            throw std::logic_error("Undirected graph doesn't contain all of input vertexes!");
        }
        int a_idx         = V_Index_Map[a_vex];
        int b_idx         = V_Index_Map[b_vex];
        Mat[a_idx][b_idx] = (if_delete) ? 0 : 1;
        Mat[b_idx][a_idx] = (if_delete) ? 0 : 1;
    }
    void ArcOpt(const int& a_idx, const int& b_idx, bool if_delete = false) {
        bool if_a_out_of_range = a_idx < 0 || a_idx >= size;
        bool if_b_out_of_range = b_idx < 0 || b_idx >= size;
        if (if_a_out_of_range || if_b_out_of_range) {
            throw std::out_of_range("Input indexes have at least one which is out of range!");
        }
        Mat[a_idx][b_idx] = (if_delete) ? 0 : 1;
        Mat[b_idx][a_idx] = (if_delete) ? 0 : 1;
    }
    void InsertArc(const T& a_vex, const T& b_vex) {
        ArcOpt(a_vex, b_vex);
    }
    void InsertArc(const int& a_idx, const int& b_idx) {
        ArcOpt(a_idx, b_idx);
    }
    void DeleteArc(const T& a_vex, const T& b_vex) {
        ArcOpt(a_vex, b_vex, true);
    }
    void DeleteArc(const int& a_idx, const int& b_idx) {
        ArcOpt(a_idx, b_idx, true);
    }
};

} // namespace DS