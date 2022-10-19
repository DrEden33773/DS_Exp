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
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class CountOff_Solution_Generator;

class CountOff : protected DS::BasicInfoCircleList {
    friend class CountOff_Solution_Generator;
    using BasicInfoCircleList::BasicInfoCircleList;

public:
    int out_freq = 1;

    /**
     * @brief @b delete_the_ptr @b (WITH_UPDATE)
     * @note
            attention! param type must be @b reference_to_ptr
            or anything changed to @b ptr_var won't come out the filed

            that's something @b unimaginable_at_first but @b reasonable_at_last

            any param transport between functions in CPP is @b value_transport
            that means @b any_param is @b a_kind_of_variable instead of @b actual_address

            took this for example =>
                node* the_ptr => address_var, not the address of an var
                node*& the_ptr => address_var, which address point to another address_var

            node* the_ptr = another => @b var_assign
                just like `int input_param = 1` in function, it won't come out of the field
     * @param the_ptr
     */
    void delete_the_ptr(node*& the_ptr) {
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

        std::string              storage;
        std::vector<std::string> res;

        node* curr     = head;
        int   curr_num = 1;

        while (size > 1) {
            int curr_modded_num = curr_num % out_freq;
            if (curr_modded_num == 0) {
                res.push_back(curr->element);
                // node* to_update = curr->next;
                delete_the_ptr(curr);
                // curr = to_update;
            } else {
                curr = curr->next;
            }
            ++curr_num;
        }
        res.push_back(curr->element); // the last one

        for (auto&& elem : res) {
            std::cout << elem << " ";
        }

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
        std::cout << "Input information (Must separate in space) => " << std::endl;
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