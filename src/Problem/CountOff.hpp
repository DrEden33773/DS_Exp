/**
 * @file CountOff.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Count_Off with Quit and Check_Remained
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../DS/LinkedList/BasicCircleList.hpp"
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

class CountOff_Solution_Generator;

class CountOff : protected DS::BasicInfoCircleList {
    friend class CountOff_Solution_Generator;
    using BasicInfoCircleList::BasicInfoCircleList;

public:
    int  out_freq = 1;
    void delete_the_ptr(node* the_ptr) {
        if (size == 1) {
            return;
        }

        bool if_the_ptr_head = the_ptr == head;
        bool if_the_ptr_tail = the_ptr == tail;

        node* prev_ptr = the_ptr->prev;
        node* next_ptr = the_ptr->next;
        prev_ptr->next = next_ptr;
        next_ptr->prev = prev_ptr;

        delete the_ptr;
        --size;

        the_ptr = next_ptr; // update the_ptr

        if (if_the_ptr_head) {
            head = tail->next;
        }
        if (if_the_ptr_tail) {
            tail = head->prev;
        }
    }
    void operate() {
        std::cout << std::endl;

        std::string storage;

        node* curr     = head;
        int   curr_num = 1;

        while (size > 1) {
            int curr_modded_num = curr_num % out_freq;
            if (curr_modded_num == 0) {
                std::cout << curr->element << " ";
                delete_the_ptr(curr);
            } else {
                curr = curr->next;
            }
            ++curr_num;
        }
        std::cout << curr->element << " "; // the last one

        std::cout << std::endl;
    }
};

class CountOff_Solution_Generator {
    CountOff_Solution_Generator() = default;
    CountOff* data                = nullptr;

public:
    ~CountOff_Solution_Generator() = default;

    void generate_model() {
        int                      num_of_person = 0;
        int                      the_freq      = 1;
        std::vector<std::string> initList;

        std::cout << std::endl;

        //
        while (true) {
            std::cout << std::endl;
            std::cout << "Input num of person(>0) => ";
            std::cin >> num_of_person;
            if (num_of_person <= 0) {
                std::cout << std::endl;
                std::cout << "Num of person should >0. " << std::endl;
            } else {
                break;
            }
        }
        initList.reserve(num_of_person);

        //
        std::cout << std::endl;
        std::cout << "Input information => " << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < num_of_person; ++i) {
            std::string curr;
            std::cin >> curr;
            initList.emplace_back(curr);
        }

        //
        while (true) {
            std::cout << std::endl;
            std::cout << "Input frequency(>0) => ";
            std::cin >> the_freq;
            if (num_of_person <= 0) {
                std::cout << std::endl;
                std::cout << "Frequency should >0. " << std::endl;
            } else {
                break;
            }
        }

        data           = new CountOff(std::move(initList));
        data->out_freq = the_freq;
    }
    void give_result() {
        data->operate();
    }

    static void Solution() {
        CountOff_Solution_Generator TheSolution;
        TheSolution.generate_model();
        TheSolution.give_result();
    }
};