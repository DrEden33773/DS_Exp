/**
 * @file call_func_in_main.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief call_func_in_main
 * @version 0.1
 * @date 2022-11-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstdlib>

const int MAX_SIZE = 2048;
struct SeqList {
    int Data[MAX_SIZE];
    int cnt;
};
typedef struct SeqList SeqList;

void DeleteBetween(SeqList* toDelete, int max, int min) {
    // DO SOMETHING
}

int main() {
    SeqList* test = (SeqList*)malloc(sizeof(SeqList));
    DeleteBetween(test, 1, 10);
    return 0;
}