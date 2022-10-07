/**
 * @file OperatorOverload.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief To show `Operator Overload`
 * @version 0.1
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>

struct elem {
    int p;

    bool operator==(elem other) {
        return this->p == other.p;
    };
};

int main() {
    elem A;
    A.p = 1;
    elem B;
    B.p = 1;
    std::cout << (A == B) << std::endl;
}