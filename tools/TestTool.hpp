/**
 * @file TestTool.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief A tool to show information of current unit test
 * @version 0.1
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <iostream>

namespace Tool {

void title_info(const char* name) {
    std::cout << "========== Test of `"
              << name
              << "` is started ========== " << std::endl;
    std::cout << std::endl;
}

void end_info(const char* name) {
    std::cout << "========== Test of `"
              << name
              << "` is ended ========== " << std::endl;
    std::cout << std::endl;
}

} // namespace Tool