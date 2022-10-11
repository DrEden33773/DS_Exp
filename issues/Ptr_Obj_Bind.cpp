/**
 * @file Ptr_Obj_Bind.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

struct LNode {
    int           v;
    struct LNode* next;
};

using LNode    = struct LNode;
using LinkList = LNode*;

void func(LinkList& L) {
    LNode* p;
    while (L->next != nullptr) {
        p = L->next;
    }
}