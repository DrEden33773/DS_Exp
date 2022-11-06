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

#include <unordered_map>
#include <utility>
#include <vector>
namespace DS {

template <typename T>
class UndirectedGraph {
    using UG = UndirectedGraph<T>;

private:
    std::vector<std::vector<int>> Mat;
    std::unordered_map<T, int>    V_Map;

public:
    ~UndirectedGraph() = default;

    UndirectedGraph(const UG& copied)
        : Mat(copied.Mat)
        , V_Map(copied.V_Map) { }
    UndirectedGraph& operator=(const UG& copied) {
        if (&copied == this) {
            return *this;
        }
        Mat   = copied.Mat;
        V_Map = copied.V_Map;
        return *this;
    }

    UndirectedGraph(UG&& moved) noexcept
        : Mat(std::move(moved.Mat))
        , V_Map(std::move(moved.V_Map)) { }
    UndirectedGraph& operator=(UG&& moved) noexcept {
        Mat   = std::move(moved.Mat);
        V_Map = std::move(moved.V_Map);
        return *this;
    }
};

} // namespace DS