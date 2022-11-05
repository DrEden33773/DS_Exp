/**
 * @file for_loop.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief for_loop
 * @version 0.1
 * @date 2022-11-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstdio>

int main() {
    printf("输入元素个数：");
    int num = 0;
    scanf("%d", &num);
    printf("依次输入 %d 个元素：\n", num);
    for (int i = 1; i <= num; ++i) {
        int element = 0;
        scanf("%d", &element);
        // 然后这里调用 `插入至线性表` 的函数
    }
    return 0;
}