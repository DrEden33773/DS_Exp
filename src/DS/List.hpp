/**
 * @file List.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief An Implementation of `STL_LIST`
 * @structure:
        null <- head <-> [data|ptr]<->...<->[data|ptr] <-> tail -> null
 *
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <unordered_map>

namespace DS {

template <typename T>
class ChainedQueue;

template <typename T>
class List {
    friend class ChainedQueue<T>;

    struct node {
        T     element;
        node* next = nullptr;
        node* prev = nullptr;
        node()     = default;
        constexpr explicit node(const T& element)
            : element(element) { }
    };
    node* head    = nullptr; // head node never maintain data
    node* tail    = nullptr; // tail node never maintain data
    bool  if_init = false;   // if init head node
    int   size    = 0;

    /// @brief @b return_name
    virtual const char* return_name() final {
        return "List";
    }

public:
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

        constexpr T&   operator*() const { return ptr->element; }
        constexpr T*   operator->() const { return &(ptr->element); }
        constexpr bool operator!=(const iterator& rhs) const { return ptr != rhs.ptr; }
        constexpr bool operator==(const iterator& rhs) const { return ptr == rhs.ptr; }

        bool operator>(const iterator& rhs) const {
            return List::if_A_behind_B(this->ptr, rhs.ptr);
        }
        bool operator>=(const iterator& rhs) const {
            bool behind = List::if_A_behind_B(this->ptr, rhs.ptr);
            bool eq     = List::if_A_is_B(this->ptr, rhs.ptr);
            return behind || eq;
        }
        bool operator<(const iterator& rhs) const {
            return List::if_A_ahead_B(this->ptr, rhs.ptr);
        }
        bool operator<=(const iterator& rhs) const {
            bool ahead = List::if_A_ahead_B(this->ptr, rhs.ptr);
            bool eq    = List::if_A_is_B(this->ptr, rhs.ptr);
            return ahead || eq;
        }
    };
    constexpr iterator begin() {
        return iterator(head->next);
    }
    constexpr iterator end() {
        return iterator(tail);
    }
    constexpr iterator Head_() {
        return iterator(head);
    }
    constexpr iterator Tail_() {
        return iterator(tail);
    }

private:
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
    static List<T> CreateList(
        std::initializer_list<T>&& initList
    ) {
        using original_type = std::initializer_list<T>;
        List<T> created(std::forward<original_type>(initList));
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

    /// @brief @b head_and_tail_opt
    void init_head_and_tail() {
        head       = new node();
        tail       = new node();
        head->next = tail;
        tail->prev = head;
        if_init    = true;
    }
    void delete_head_and_tail() {
        delete head;
        delete tail;
        head = nullptr;
        tail = nullptr;
    }

    /// @brief object management
    List() { // default constructor (not recommended!)
        init_head_and_tail();
    }
    List(const List& copied) { // copy constructor
        init_head_and_tail();
        for (auto&& element : copied) {
            push_back(element);
        }
    }
    List& operator=(const List& copied) {
        if (&copied == this) { // self copy
            return *this;
        }
        init_head_and_tail();
        for (auto&& element : copied) {
            push_back(element);
        }
        return *this;
    }
    List(List&& moved) noexcept
        : tail(moved.tail)
        , head(moved.head)
        , if_init(true)
        , size(moved.size) { // move constructor

        // 1. locate each node of `this` && set null to each node of `moved`
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
    List& operator=(List&& moved) noexcept {
        tail    = moved.tail;
        head    = moved.head;
        if_init = true;
        size    = moved.size;
        // 1. locate each node of `this` && set null to each node of `moved`
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

        return *this;
    }
    List(std::initializer_list<T>&& initList) {
        init_head_and_tail();
        for (const T& element : initList) {
            push_back(element);
        }
    }
    ~List() noexcept { // impossible to throw exception
        while (size) { // could rely on size
            pop_back();
        }
        delete_head_and_tail();
    }

    /// @brief node_opt

    /**
     * @brief delete_a_node and return next_of `deleted`
     *
     * @param toDel
     * @return node*
     */
    node* delete_a_node(node* toDel) {
        if (toDel == head || toDel == tail) {
            throw std::logic_error("NEVER try to delete `head` or `tail` nodes!");
        }
        node* thePrev = toDel->prev;
        node* theNext = toDel->next;
        thePrev->next = theNext;
        theNext->prev = thePrev;
        delete toDel;
        --size;

        return theNext;
    }
    node* link_a_node(node* thePrev, node* toLink, node* theNext) {
        if (theNext == head || thePrev == tail) {
            throw std::logic_error("NEVER try to add node ahead of `head` or after `tail` nodes!");
        }
        thePrev->next = toLink;
        toLink->prev  = thePrev;
        toLink->next  = theNext;
        theNext->prev = toLink;

        return toLink;
    }
    node* link_a_node_after(node* thePrev, node* toLink) {
        return link_a_node(thePrev, toLink, thePrev->next);
    }
    node* link_a_node_before(node* theNext, node* toLink) {
        return link_a_node(theNext->prev, toLink, theNext);
    }
    node* unlink_a_node(node* toUnlink) {
        if (toUnlink == head || toUnlink == tail) {
            throw std::logic_error("NEVER try to unlink `head` or `tail` node!");
        }
        node* thePrev = toUnlink->prev;
        node* theNext = toUnlink->next;

        toUnlink->prev = nullptr;
        toUnlink->next = nullptr;

        thePrev->next = theNext;
        theNext->prev = thePrev;

        return toUnlink;
    }
    node* take_down_a_node(node* toTakeDown) {
        node* toReturn = unlink_a_node(toTakeDown);
        --size;
        return toReturn;
    }
    void add_a_node_after_head(node* toAdd) {
        link_a_node_after(head, toAdd);
        ++size;
    }
    void add_a_node_before_tail(node* toAdd) {
        link_a_node_before(tail, toAdd);
        ++size;
    }
    void swap_node(node* a, node* b) {
        node* a_prev = a->prev;
        node* a_next = a->next;
        node* b_prev = b->prev;
        node* b_next = b->next;
        unlink_a_node(a);
        unlink_a_node(b);
        link_a_node(a_prev, b, a_next);
        link_a_node(b_prev, a, b_next);
    }

    /// @brief data_io operation
    T pop_back() { // remove `tail->prev`
        if (head->next == tail) {
            throw std::out_of_range("There's NO node in this linked list!");
        }
        T to_return = tail->prev->element;
        delete_a_node(tail->prev);
        return to_return;
    }
    T pop_front() { // remove `head->next`
        if (head->next == tail) {
            throw std::out_of_range("There's NO node in this linked list!");
        }
        T returned_elem = head->next->element;
        delete_a_node(head->next);
        return returned_elem;
    }
    void push_back(const T& input) {
        if (!if_init) {
            throw std::out_of_range("The linked list hasn't been initialized!");
        }
        node* to_add  = new node(input);
        node* thePrev = tail->prev;
        node* theNext = tail;
        link_a_node(thePrev, to_add, theNext);
        ++size;
    }
    void push_front(const T& input) {
        if (!if_init) {
            throw std::out_of_range("The linked list hasn't been initialized!");
        }
        node* to_add  = new node(input);
        node* thePrev = head;
        node* theNext = head->next;
        link_a_node(thePrev, to_add, theNext);
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
        if (pos < 1 || pos > size) {
            throw std::out_of_range("The insert position is out of range!");
        }
        auto&& insert_place        = Head_() + pos;
        auto&& before_insert_place = insert_place - 1;

        node* toInsert = new node(element);
        node* theNext  = insert_place.ptr;
        node* thePrev  = before_insert_place.ptr;

        link_a_node(thePrev, toInsert, theNext);
    }
    void insert_to(const T& element, int pos) {
        insert_elem(element, pos);
    }
    T set_elem(const T& element, int pos) {
        if (pos < 1 || pos > size) {
            throw std::out_of_range("The insert position is out of range!");
        }
        auto&& locator      = Head_() + pos; // let the iterator jump instead
        node*  index_node   = locator.ptr;   // unwrap the iterator, get the raw ptr
        auto&& old          = index_node->element;
        index_node->element = element;
        return old;
    }
    T set_to(const T& element, int pos) {
        set_elem(element, pos);
    }
    T get_elem(int pos) {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot get any element!");
        }
        if (pos < 1 || pos > size) {
            throw std::out_of_range("The position is out of range!");
        }
        auto&& locator    = Head_() + pos; // let the iterator jump instead
        node*  index_node = locator.ptr;   // unwrap the iterator, get the raw ptr
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
            throw std::out_of_range("The position is out of range!");
        }
        // remove `tail` or `head->next`
        if (index == size - 1) {
            pop_back();
            return;
        } else if (index == 0) {
            pop_front();
            return;
        }
        iterator locator = begin() + index;
        delete_a_node(locator.ptr);
    }
    int locate_elem(const T& elem) {
        if (size == 0) {
            throw std::logic_error("The size is zero, cannot locate any element!");
        }
        int    res        = 0;
        auto&& iter       = begin();
        int    curr_index = 0;
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
        auto&& res_iter = begin() + (elem_index - 1);
        node*  res_ptr  = res_iter.ptr;
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
        auto&& res_iter = begin() + (elem_index + 1);
        node*  res_ptr  = res_iter.ptr;
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
    void std_sort(bool if_ascending = true) {
        if (head->next == nullptr) {
            std::cout << return_name() << " is empty, will escape sorting. " << std::endl;
            std::cout << std::endl;
        }
        if (if_ascending) {
            std::sort(begin(), end());
        } else {
            std::sort(begin(), end(), [](const T& a, const T& b) {
                return a > b;
            });
        }
        std::cout << return_name() << " called std::sort()" << std::endl;
        std::cout << std::endl;
    }
    void reverse() {
        if (head->next == tail) {
            return;
        }

        node* new_head = new node();
        node* new_tail = new node();
        new_head->next = new_tail;
        new_tail->prev = new_head;

        while (head->next != tail) {
            node* unlinked = unlink_a_node(head->next);
            link_a_node_after(new_head, unlinked);
        }

        delete_head_and_tail();
        head = new_head;
        tail = new_tail;
    }

    /// @brief @b unique
    void hash_unique() {
        if (head->next == tail) {
            return;
        }

        std::unordered_map<T, bool> hashmap;

        node* curr = head->next;
        while (curr != tail) {
            if (!hashmap.contains(curr->element)) {
                hashmap[curr->element] = true;
                curr                   = curr->next;
            } else {
                // to delete
                curr = delete_a_node(curr);
            }
        }
    }
    void emplace_unique() {
        if (head->next == tail) {
            return;
        }

        node* outer = head->next;
        while (outer->next != tail) {
            node* inner = outer->next;
            while (inner != tail) {
                if (inner->element == outer->element) {
                    inner = delete_a_node(inner);
                } else {
                    inner = inner->next;
                }
            }
            outer = outer->next;
        }
    }
    void ordered_unique() {
        if (head->next == tail) {
            return;
        }

        T     previous_elem = head->next->element;
        node* cmp           = head->next->next;
        while (cmp != tail) {
            if (cmp->element == previous_elem) {
                cmp = delete_a_node(cmp);
            } else {
                previous_elem = cmp->element;
                cmp           = cmp->next;
            }
        }
    }
    void unique(bool if_emplace = false) {
        if (!if_emplace) {
            hash_unique();
        } else {
            emplace_unique();
        }
    }

    /// @brief @b merge_then_unique
    static void Merge_Unique(List<T>& A, List<T>& B, bool if_ascending = true)
    requires std::equality_comparable<T>
    {
        A.std_sort(if_ascending);
        B.std_sort(if_ascending);

        List<T> C = std::move(A); // A is cleared (without head and tail)
        A.init_head_and_tail();

        // now, compare on `B` and `C`
        node* b = B.head->next;
        node* c = C.head->next;
        while (b != B.tail && c != C.tail) {
            bool  B_greater_than_C = b->element > c->element;
            bool  B_eq_C           = b->element == c->element;
            bool  B_less_than_C    = b->element < c->element;
            node* b_next           = b->next;
            node* c_next           = c->next;
            if (B_eq_C) {
                // B == C

                // delete node in C, move node in B
                node* fetched = B.take_down_a_node(b);
                C.delete_a_node(c);
                A.add_a_node_before_tail(fetched);
                // update all nodes
                b = b_next;
                c = c_next;
            } else if (B_greater_than_C) {
                // B > C
                node* fetched = nullptr;
                if (if_ascending) {
                    // Fetch/Update smaller one
                    fetched = C.take_down_a_node(c);
                    c       = c_next;
                } else {
                    // Fetch/Update bigger one
                    fetched = B.take_down_a_node(b);
                    b       = b_next;
                }
                A.add_a_node_before_tail(fetched);
            } else {
                // B < C
                node* fetched = nullptr;
                if (if_ascending) {
                    // Fetch/Update smaller one
                    fetched = B.take_down_a_node(b);
                    b       = b_next;
                } else {
                    // Fetch/Update bigger one
                    fetched = C.take_down_a_node(c);
                    c       = c_next;
                }
                A.add_a_node_before_tail(fetched);
            }
        }
        while (b != B.tail) {
            node* b_next  = b->next;
            node* fetched = B.take_down_a_node(b);
            A.add_a_node_before_tail(fetched);
            b = b_next;
        }
        while (c != C.tail) {
            node* c_next  = c->next;
            node* fetched = C.take_down_a_node(c);
            A.add_a_node_before_tail(fetched);
            c = c_next;
        }

        A.ordered_unique();
    }
};

} // namespace DS