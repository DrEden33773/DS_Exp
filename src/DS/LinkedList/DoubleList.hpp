/**
 * @file DoubleList.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Linked list with two directions
 * @structure:
        head<->[data|ptr]<->[data|ptr]<->...<->[data|ptr]-> nullptr
                                                ^^^^------> tail
 * @version 0.1
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <unordered_map>

namespace DS {

template <typename T = int> // default type = int
class DoubleList {          // all public, for algorithm
    static const std::string DSname;

    struct node {
        T     element;
        node* next = nullptr;
        node* prev = nullptr;
        node()     = default;
        constexpr explicit node(const T& element)
            : element(element) { }
    };
    node* head    = nullptr; // head node never maintain data
    node* tail    = nullptr; // tail node always maintain data
    bool  if_init = false;   // if init head node
    int   size    = 0;       // num of nodes (except head node)
                             // (num of effective nodes)
    bool if_moved = false;   // if temporarily created object will be moved
                             // if so, deleter won't be called

    /// @brief @b return_name
    virtual const char* return_name() final {
        return "Double-List";
    }

    /// @brief @b bidirectional_iterator
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        node* ptr = nullptr;

        constexpr explicit iterator(node* ptr)
            : ptr(ptr) { }

        iterator operator++() {
            ptr = ptr->next;
            return *this;
        }
        iterator operator--() {
            ptr = ptr->prev;
            return *this;
        }
        iterator operator++(int any) {
            iterator old = *this;

            operator++();
            return old;
        }
        iterator operator--(int any) {
            iterator old = *this;

            operator--();
            return old;
        }
        iterator operator+(int distance) {
            iterator res = *this;
            if (distance > 0) {
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->next;
                }
            } else if (distance < 0) { // change to the abs value
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->prev;
                }
            }
            return res;
        }
        iterator operator-(int distance) {
            iterator res = *this;
            if (distance > 0) {
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->prev;
                }
            } else if (distance < 0) { // change to the abs value
                distance *= -1;
                for (int tmp = 0; tmp < distance; ++tmp) {
                    res.ptr = res.ptr->next;
                }
            }
            return res;
        }
        iterator operator+=(int n) {
            iterator tmp = (*this) + n;
            this->ptr    = tmp.ptr;
            return *this;
        }
        iterator operator-=(int n) {
            iterator tmp = (*this) - n;
            this->ptr    = tmp.ptr;
            return *this;
        }

        int operator-(const iterator& rhs) {
            // assume that `rhs` -> ... -> `this` (will be verified later)
            int   distance           = 0;
            node* this_ptr           = this->ptr;
            node* rhs_ptr            = rhs.ptr;
            node* original_rhs_ptr   = rhs.ptr;
            bool  if_rhs_behind_this = false;
            while (rhs_ptr != nullptr) {
                if (rhs_ptr == this->ptr) {
                    break;
                }
                rhs_ptr = rhs_ptr->next;
                ++distance;
            } // maybe rhs.ptr == nullptr
            if (rhs_ptr == nullptr) {
                if_rhs_behind_this = true;
            }
            if (if_rhs_behind_this) {
                rhs_ptr  = original_rhs_ptr;
                distance = 0;
                // now `this` -> ... -> `rhs`
                while (this_ptr != nullptr) {
                    if (this_ptr == rhs_ptr) {
                        break;
                    }
                    this_ptr = this_ptr->next;
                    ++distance;
                }
            }
            return distance;
        }

        T&   operator*() const { return ptr->element; }
        T*   operator->() const { return &(ptr->element); }
        bool operator!=(const iterator& rhs) const { return ptr != rhs.ptr; }
        bool operator==(const iterator& rhs) const { return ptr == rhs.ptr; }
        bool operator>(const iterator& rhs) const {
            return DoubleList::if_A_behind_B(this->ptr, rhs.ptr);
        }
        bool operator>=(const iterator& rhs) const {
            bool behind = DoubleList::if_A_behind_B(this->ptr, rhs.ptr);
            bool eq     = DoubleList::if_A_is_B(this->ptr, rhs.ptr);
            return behind || eq;
        }
        bool operator<(const iterator& rhs) const {
            return DoubleList::if_A_ahead_B(this->ptr, rhs.ptr);
        }
        bool operator<=(const iterator& rhs) const {
            bool ahead = DoubleList::if_A_ahead_B(this->ptr, rhs.ptr);
            bool eq    = DoubleList::if_A_is_B(this->ptr, rhs.ptr);
            return ahead || eq;
        }
    };
    iterator begin() {
        return iterator(head->next);
    }
    iterator end() {
        return iterator(tail->next);
    }
    /// @b each operation related to iterator will be in @b [begin(),end()) range

    /// @brief relative location relation resolver
    static bool if_A_ahead_B(node* A, node* B) { // A -> ... -> B
        bool  res = false;
        node* tmp = A;
        while (tmp != nullptr) {
            if (tmp == B) {
                res = true;
                break;
            }
            tmp = tmp->next;
        }
        return res;
    }
    static bool if_A_behind_B(node* A, node* B) { // B -> ... -> A
        bool  res = false;
        node* tmp = B;
        while (tmp != nullptr) {
            if (tmp == A) {
                res = true;
                break;
            }
            tmp = tmp->next;
        }
        return res;
    }
    static constexpr bool if_A_is_B(node* A, node* B) { // B == A
        return A == B;
    }
    static constexpr bool if_A_is_not_B(node* A, node* B) { // B != A
        return A != B;
    }

public:
    /// @brief static constructor
    static DoubleList<T> CreateDoubleList(
        std::initializer_list<T>&& initList
    ) {
        using original_type = std::initializer_list<T>;
        DoubleList<T> created(std::forward<original_type>(initList));
        return created;
    }

    /// @brief constexpr operation
    constexpr bool if_empty() noexcept {
        return this->size == 0;
    }
    constexpr int get_length() noexcept {
        return this->size;
    }
    constexpr int get_size() noexcept {
        return this->size;
    }

    /// @brief object management
    DoubleList() { // default constructor (not recommended!)
        init_head();
    }
    DoubleList(const DoubleList& copied) { // copy constructor
        init_head();
        for (const T& element : copied) {
            push_back(element);
        }
    }
    DoubleList(DoubleList&& moved) noexcept { // move constructor

        // 1. guarantee `this`
        if_init = true;
        size    = moved.size;
        // (1) => locate head and tail
        head = moved.head;
        tail = moved.tail;
        // (2) => locate each node of `this` && set null to each node of `moved`
        node* curr      = head;
        node* tmp_moved = moved.head;
        while (tmp_moved != nullptr) {
            // link node in `this` with moved
            curr       = tmp_moved;
            curr->next = tmp_moved->next;
            curr->prev = tmp_moved->prev;
            curr       = curr->next;
            // free moved
            node* tmp_moved_next = tmp_moved->next;
            tmp_moved            = nullptr;
            tmp_moved            = tmp_moved_next;
        }
        // 2. clear the property of `moved` one
        moved.head    = nullptr;
        moved.tail    = nullptr;
        moved.size    = 0;
        moved.if_init = false;
    }
    DoubleList(std::initializer_list<T>&& initList) {
        init_head();
        for (const T& element : initList) {
            push_back(element);
        }
    }
    ~DoubleList() noexcept { // impossible to throw exception
        if (if_moved) {
            return;
        }
        while (tail != head) { // do not rely on size, will be better!
            pop_back();
        }
        delete_head();
    }

    /// @brief head_node operation
    void init_head() {
        head    = new node();
        tail    = head;
        if_init = true;
    }
    void delete_head() {
        if (head) {
            delete head;
        }
    }

    /// @brief data_io operation
    T pop_back() { // remove `tail`
        if (tail == nullptr || tail == head) {
            throw std::out_of_range("There's NO node in this linked list!");
        }
        node* new_tail  = tail->prev;
        node* old_tail  = tail;
        T     to_return = old_tail->element;
        new_tail->next  = nullptr;
        delete tail;
        tail = new_tail;
        --size;
        return to_return;
    }
    T pop_front() { // remove `head->next`
        if (tail == nullptr || tail == head) {
            throw std::out_of_range("There's NO node in this linked list!");
        }
        node* deleted       = head->next;
        node* new_head_next = deleted->next;
        T     returned_elem = deleted->element;
        head->next          = new_head_next;
        new_head_next->prev = head;
        delete deleted;
        --size;
        if (size == 0) {
            tail = head;
        }
        return returned_elem;
    }
    void push_back(const T& input) {
        if (!if_init) {
            throw std::out_of_range("The linked list hasn't been initialized!");
        }
        node* to_add = new node(input);
        if (tail == nullptr) {
            head->next = to_add;
            tail       = to_add;
            tail->prev = head;
        } else {
            tail->next   = to_add;
            to_add->prev = tail;
            tail         = to_add;
        }
        ++size;
    }
    void push_front(const T& input) {
        if (!if_init) {
            throw std::out_of_range("The linked list hasn't been initialized!");
        }
        node* to_add = new node(input);
        if (tail == nullptr) {
            head->next = to_add;
            tail       = to_add;
            tail->prev = head;
        } else {
            node* the_next = head->next;
            to_add->next   = the_next;
            if (the_next != nullptr) { // or, the_next == nullptr
                the_next->prev = to_add;
            }
            to_add->prev = head;
            head->next   = to_add;
            if (tail == head) {
                tail = to_add;
            }
        }
        ++size;
    }
    void add_back(const T& input) {
        push_back(input);
    }
    void add_front(const T& input) {
        add_front(input);
    }

    /// @brief element operation
    /// => each input/output int is `actual index + 1` (position)!
    void insert_elem(const T& element, int pos) {
        int index = pos - 1;
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The insert position is out of range!");
        }
        if (index == size - 1) {
            push_back(element);
            return;
        }
        // common occasion => insert into the middle part
        iterator locator          = begin() + index;
        node*    insert_ptr       = locator.ptr;
        node*    prior_insert_ptr = insert_ptr->prev;

        node* tmp              = new node(element);
        prior_insert_ptr->next = tmp;
        tmp->prev              = prior_insert_ptr;
        tmp->next              = insert_ptr;
        insert_ptr->prev       = tmp;
        ++size;
    }
    void insert_to(const T& element, int pos) {
        insert_elem(element, pos);
    }
    T set_elem(const T& element, int pos) {
        int index = pos - 1;
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The insert position is out of range!");
        }
        iterator locator    = begin() + index; // let the iterator jump instead
        node*    index_node = locator.ptr;     // unwrap the iterator, get the raw ptr
        T        old        = index_node->element;
        index_node->element = element;
        return old;
    }
    T set_to(const T& element, int pos) {
        set_elem(element, pos);
    }
    T get_elem(int pos) {
        int index = pos - 1;
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot get any element!");
        }
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The insert position is out of range!");
        }
        iterator locator    = begin() + index; // let the iterator jump instead
        node*    index_node = locator.ptr;     // unwrap the iterator, get the raw ptr
        return index_node->element;
    }
    T get(int pos) {
        return get_elem(pos);
    }
    void delete_elem(int pos) {
        int index = pos - 1;
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot delete any element!");
        }
        if (index < 0 || index > size - 1) {
            throw std::out_of_range("The insert position is out of range!");
        }
        // remove `tail` or `head->next`
        if (index == size - 1) {
            pop_back();
            return;
        } else if (index == 0) {
            pop_front();
            return;
        }
        iterator locator      = begin() + index;
        node*    prior_delete = locator.ptr->prev;
        node*    to_delete    = locator.ptr;
        node*    next_delete  = locator.ptr->next;
        prior_delete->next    = next_delete;
        next_delete->prev     = prior_delete;
        delete to_delete;
        --size;
    }
    int locate_elem(const T& elem) {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot locate any element!");
        }
        int      res        = 0;
        iterator iter       = begin();
        int      curr_index = 0;
        while (iter.ptr != nullptr) {
            if (iter.ptr->element == elem) {
                res = curr_index + 1;
                break;
            }
            ++iter;
            ++curr_index;
        }
        return res;
    }
    T prior_elem(const T& elem) {
        int elem_index = locate_elem(elem) - 1;
        if (elem_index == -1) {
            throw std::logic_error("Cannot find input element!");
        } else if (elem_index == 0) {
            throw std::logic_error(
                "The first input element lies in the head, without any prior element!"
            );
        }
        iterator res_iter = begin() + (elem_index - 1);
        node*    res_ptr  = res_iter.ptr;
        return res_ptr->element;
    }
    T next_elem(const T& elem) {
        int elem_index = locate_elem(elem) - 1;
        if (elem_index == -1) {
            throw std::logic_error("Cannot find input element!");
        } else if (elem_index == size - 1) {
            throw std::logic_error(
                "The first input element lies in the tail, without any next element!"
            );
        }
        iterator res_iter = begin() + (elem_index + 1);
        node*    res_ptr  = res_iter.ptr;
        return res_ptr->element;
    }

    /// @brief function
    void echo() {
        std::cout << "range-based loop => ";
        bool if_empty = true;
        for (const T& element : *this) { // this will use the iterator
            std::cout << element << " ";
            if_empty = false;
        }
        if (if_empty) {
            std::cout << "empty. ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    void std_sort() {
        if (head->next == nullptr) {
            std::cout << return_name() << " is empty, will escape sorting. " << std::endl;
            std::cout << std::endl;
        }
        std::sort(begin(), end());
        std::cout << return_name() << " called std::sort()" << std::endl;
        std::cout << std::endl;
    }
    void insert_sort(bool if_ascending = true) { // ascending order
        /// @a could_be_recommended ==> (discarded)
        if (head->next == nullptr) {
            std::cout << return_name() << " is empty, will escape sorting. " << std::endl;
            std::cout << std::endl;
            return;
        }
        DoubleList<T>& curr = *this;
        for (int index = 1; index < size; ++index) {
            int opt = index;
            if (if_ascending) {
                while (opt > 0 && curr[opt] < curr[opt - 1]) {
                    // from: front => ahead => back => end
                    //   to: front => back => ahead => end
                    node* front = nullptr;
                    node* ahead = nullptr;
                    node* back  = nullptr;
                    node* end   = nullptr;
                    back        = (begin() + (opt)).ptr;
                    ahead       = back->prev;
                    end         = back->next;
                    if (opt - 2 == -1) {
                        front = head; // important operation
                    } else {
                        front = back->prev->prev;
                    }
                    //
                    front->next = back;
                    back->prev  = front;
                    //
                    back->next  = ahead;
                    ahead->prev = back;
                    //
                    ahead->next = end;
                    end->prev   = ahead;
                    --opt;
                }
            } else {
                while (opt > 0 && curr[opt] > curr[opt - 1]) {
                    // from: front => ahead => back => end
                    //   to: front => back => ahead => end
                    node* front = nullptr;
                    node* ahead = nullptr;
                    node* back  = nullptr;
                    node* end   = nullptr;
                    back        = (begin() + (opt)).ptr;
                    ahead       = back->prev;
                    end         = back->next;
                    if (opt - 2 == -1) {
                        front = head; // important operation
                    } else {
                        front = back->prev->prev;
                    }
                    //
                    front->next = back;
                    back->prev  = front;
                    //
                    back->next  = ahead;
                    ahead->prev = back;
                    //
                    ahead->next = end;
                    end->prev   = ahead;
                    --opt;
                }
            }
        }
        std::cout << return_name() << " called insert_sort()" << std::endl;
        std::cout << std::endl;
    }
    void select_sort(bool if_ascending = true) { // ascending order
        if (head->next == nullptr) {
            std::cout << return_name() << " is empty, will escape sorting. " << std::endl;
            std::cout << std::endl;
            return;
        }
        DoubleList<T>& curr = *this;
        for (node* outer = head->next; outer != tail; outer = outer->next) {
            T&    outer_elem = outer->element;
            node* lim_ptr    = outer;
            if (if_ascending) {
                for (node* inner = outer->next; inner != nullptr; inner = inner->next) {
                    T& inner_elem = inner->element;
                    if (inner_elem < lim_ptr->element) {
                        lim_ptr = inner;
                    }
                } // lim_ptr found the correct place
            } else {
                for (node* inner = outer->next; inner != nullptr; inner = inner->next) {
                    T& inner_elem = inner->element;
                    if (inner_elem > lim_ptr->element) {
                        lim_ptr = inner;
                    }
                } // lim_ptr found the correct place
            }
            T& lim_elem = lim_ptr->element;
            if (lim_ptr != outer) {
                auto tmp   = std::move(lim_elem);
                lim_elem   = std::move(outer_elem);
                outer_elem = std::move(tmp);
                // this is the best way!
                // A = std::move(B) send the ownership of B to A (move B to A),
                // instead of copy the B to A
                // so there's no copy-time-cost!

                // if you still want to use the `node exchange`
                // then you have to use iterator to get the prior node,
                // which will cost more time (because there's no `prev` ptr in the node)
            }
        }
        std::cout << return_name() << " called select_sort()" << std::endl;
        std::cout << std::endl;
    }
    void sort(bool if_ascending = true) { // ascending order
        insert_sort(if_ascending);
    }
    void reverse() {
        if (size == 0 || size == 1) {
            return; // don't need to!
        }
        node* new_tail = head->next;
        node* to_opt   = head->next;
        head->next     = nullptr;
        to_opt->prev   = nullptr;
        while (to_opt != nullptr) {
            node* tmp_next     = to_opt->next;
            node* next_of_head = head->next;
            to_opt->next       = next_of_head;
            if (next_of_head != nullptr) {
                next_of_head->prev = to_opt;
            }
            head->next   = to_opt;
            to_opt->prev = head;

            to_opt = tmp_next;
        }
        tail = new_tail;
        std::cout << return_name() << " called `reverse()`. " << std::endl;
        std::cout << std::endl;
    }
    void emplace_unique() {
        node* curr       = head->next;
        node* prior_curr = head;
        while (curr != nullptr) {
            node* cmp       = curr->next;
            node* prior_cmp = curr;
            while (cmp != nullptr) {
                node* next_cmp = cmp->next;
                if (cmp->element == curr->element) {
                    // remove cmp
                    prior_cmp->next = next_cmp;
                    if (cmp != tail) {
                        next_cmp->prev = prior_cmp;
                    }

                    if (cmp == tail) { // must judge before delete curr
                        tail = prior_cmp;
                    }
                    delete cmp;
                    --size; // important!
                    cmp = next_cmp;

                } else {
                    cmp       = next_cmp;
                    prior_cmp = prior_cmp->next;
                }
            }
            curr       = curr->next;
            prior_curr = prior_curr->next;
        }
    }
    void hash_unique() {
        std::unordered_map<T, bool> hash_table;

        node* prior_curr = head;
        node* curr       = head->next;
        while (curr != nullptr) {
            node* tmp_next  = curr->next;
            T&    curr_elem = curr->element;
            if (!hash_table.contains(curr_elem)) {
                hash_table[curr_elem] = true;
            } else if (hash_table[curr_elem]) {
                node* next_curr  = curr->next;
                prior_curr->next = next_curr;
                next_curr->prev  = prior_curr;

                if (curr == tail) { // must judge before delete curr
                    tail = prior_curr;
                }
                delete curr;
                --size;
                hash_table[curr_elem] = false;
            }
            curr       = tmp_next;
            prior_curr = prior_curr->next;
        }
    }
    void unique(bool if_emplace = false) {
        if (!if_emplace) {
            hash_unique();
        } else {
            emplace_unique();
        }
    }
    void ordered_unique() {
        if (head->next == nullptr) { // empty list
            return;
        }
        T tmp_elem = head->next->element; // do not use reference!
        // cause you need to reassign `tmp_elem` but hate to change `head->next->element`
        node* curr = head->next->next;
        while (curr != nullptr) {
            node* prior_curr = curr->prev;
            node* next_curr  = curr->next;
            if (curr->element == tmp_elem) {
                prior_curr->next = next_curr;
                next_curr->prev  = prior_curr;

                if (curr == tail) { // must judge before delete curr
                    tail = prior_curr;
                }
                delete curr;
                --size;
                curr = prior_curr->next;
            } else {
                tmp_elem = curr->element;
                curr     = curr->next;
            }
        }
    }
    static void Merge_Unique(
        DoubleList<int>& A,
        DoubleList<int>& B,
        bool             if_ascending = false
    ) {
        /// @brief this is to make sure the descending order, could escape
        A.select_sort(if_ascending); // default as descending
        B.select_sort(if_ascending); // default as descending

        DoubleList<int> C = std::move(A); // A is cleared (without head)
        A.init_head();

        node* prior_C_ptr = C.head;
        node* C_ptr       = C.head->next;
        node* prior_B_ptr = B.head;
        node* B_ptr       = B.head->next;
        while (C_ptr != nullptr && B_ptr != nullptr) {
            if (C_ptr->element < B_ptr->element) {
                // move from B
                node* next_B_ptr  = B_ptr->next;
                prior_B_ptr->next = next_B_ptr;
                if (next_B_ptr != nullptr) {
                    next_B_ptr->prev = prior_B_ptr;
                }

                A.tail->next = B_ptr;
                B_ptr->prev  = A.tail;
                A.tail       = B_ptr;
                A.tail->next = nullptr; // we need to move a single node
                ++A.size;

                B_ptr = prior_B_ptr->next;
                --B.size;
            } else if (C_ptr->element == B_ptr->element) {
                // move from B
                node* next_B_ptr  = B_ptr->next;
                prior_B_ptr->next = next_B_ptr;
                if (next_B_ptr != nullptr) {
                    next_B_ptr->prev = prior_B_ptr;
                }

                A.tail->next = B_ptr;
                B_ptr->prev  = A.tail;
                A.tail       = B_ptr;
                A.tail->next = nullptr; // we need to move a single node
                ++A.size;

                B_ptr = prior_B_ptr->next;
                --B.size;

                // remove the C
                node* next_C_ptr  = C_ptr->next;
                prior_C_ptr->next = next_C_ptr;
                if (next_C_ptr != nullptr) {
                    next_C_ptr->prev = prior_C_ptr;
                }
                delete C_ptr;
                C_ptr = prior_C_ptr->next;
                --C.size;
            } else {
                // move from C
                node* next_C_ptr  = C_ptr->next;
                prior_C_ptr->next = next_C_ptr;
                if (next_C_ptr != nullptr) {
                    next_C_ptr->prev = prior_C_ptr;
                }

                A.tail->next = C_ptr;
                C_ptr->prev  = A.tail; // fixed a bug?
                A.tail       = C_ptr;
                A.tail->next = nullptr; // we need to move a single node
                ++A.size;
                C_ptr = prior_C_ptr->next;
                --C.size;
            }
        }
        while (C_ptr != nullptr) {
            // move from C
            node* next_C_ptr  = C_ptr->next;
            prior_C_ptr->next = next_C_ptr;
            if (next_C_ptr != nullptr) {
                next_C_ptr->prev = prior_C_ptr;
            }

            A.tail->next = C_ptr;
            C_ptr->prev  = A.tail;
            A.tail       = C_ptr;
            ++A.size;
            A.tail->next = nullptr; // we need to move a single node

            C_ptr = prior_C_ptr->next;
            --C.size;
        }
        while (B_ptr != nullptr) {
            // move from B
            node* next_B_ptr  = B_ptr->next;
            prior_B_ptr->next = next_B_ptr;
            if (next_B_ptr != nullptr) {
                next_B_ptr->prev = prior_B_ptr;
            }
            A.tail->next = B_ptr;
            A.tail       = B_ptr;
            ++A.size;
            A.tail->next = nullptr; // we need to move a single node

            B_ptr = prior_B_ptr->next;
            --B.size;
        }

        // B and C List is totally empty right now
        // but we need to relocate their tail, for correct destruction
        // it's easy 'cause `tail = head` is the default state of any empty list

        B.tail = B.head;
        C.tail = C.head;

        A.ordered_unique();
    }
};

template <typename T>
const std::string DoubleList<T>::DSname = "DoubleList";

template <typename T>
using List = DoubleList<T>;

} // namespace DS