/**
 * @file Integer.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Integer, contains 'sup lim' and 'inf lim'
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <limits>

struct Integer {
    int  value          = 0;
    bool upper_lim_flag = false;
    bool lower_lim_flag = false;

    /**
     * @brief Construct a new Integer object
     *
     * @param value
     */
    explicit Integer(int value)
        : value(value) { }

    /// @brief default destructor
    ~Integer() = default;

    /**
     * @brief Copy a new Integer object
     *
     * @param copied
     */
    Integer(const Integer& copied) = default;
    Integer& operator=(const Integer& copied) {
        if (&copied == this) {
            return *this;
        }
        value          = copied.value;
        upper_lim_flag = copied.upper_lim_flag;
        lower_lim_flag = copied.lower_lim_flag;
        return *this;
    }

    /**
     * @brief Move a new Integer object
     *
     * @param moved
     */
    Integer(Integer&& moved) noexcept
        : value(moved.value)
        , upper_lim_flag(moved.upper_lim_flag)
        , lower_lim_flag(moved.lower_lim_flag) {
    }
    Integer& operator=(Integer&& moved) noexcept {
        value          = moved.value;
        upper_lim_flag = moved.upper_lim_flag;
        lower_lim_flag = moved.lower_lim_flag;
        return *this;
    }

    /**
     * @brief @b Compare_With_Integer
     *
     * @param another
     * @return true
     * @return false
     */
    bool operator==(const Integer& another) {
        bool res = false;

        bool if_this_upper_lim    = this->upper_lim_flag;
        bool if_this_lower_lim    = this->lower_lim_flag;
        bool if_another_upper_lim = another.upper_lim_flag;
        bool if_another_lower_lim = another.lower_lim_flag;
        bool if_this_lim          = if_this_lower_lim or if_this_upper_lim;
        bool if_another_lim       = if_another_lower_lim or if_another_upper_lim;

        if (!if_this_lim && !if_another_lim) {
            res = value == another.value;
        } else {
            if (if_this_upper_lim && if_another_upper_lim) {
                res = true;
            }
            if (if_this_lower_lim && if_another_lower_lim) {
                res = true;
            }
        }

        return res;
    }
    bool operator!=(const Integer& another) {
        return !(*this == another);
    }
    bool operator>(const Integer& another) {
        bool res = true;

        bool if_this_upper_lim    = this->upper_lim_flag;
        bool if_this_lower_lim    = this->lower_lim_flag;
        bool if_another_upper_lim = another.upper_lim_flag;
        bool if_another_lower_lim = another.lower_lim_flag;
        bool if_this_lim          = if_this_lower_lim || if_this_upper_lim;
        bool if_another_lim       = if_another_lower_lim || if_another_upper_lim;

        if (!if_this_lim && !if_another_lim) {
            return this->value > another.value;
        } else {
            if (if_another_upper_lim) {
                res = false;
            }
        }

        return res;
    }
    bool operator<(const Integer& another) {
        bool res = true;

        bool if_this_upper_lim    = this->upper_lim_flag;
        bool if_this_lower_lim    = this->lower_lim_flag;
        bool if_another_upper_lim = another.upper_lim_flag;
        bool if_another_lower_lim = another.lower_lim_flag;
        bool if_this_lim          = if_this_lower_lim || if_this_upper_lim;
        bool if_another_lim       = if_another_lower_lim || if_another_upper_lim;

        if (!if_this_lim && !if_another_lim) {
            return this->value < another.value;
        } else {
            if (if_this_upper_lim) {
                res = false;
            }
        }

        return res;
    }
    bool operator>=(const Integer& another) {
        return !(*this < another);
    }
    bool operator<=(const Integer& another) {
        return !(*this > another);
    }

    /**
     * @brief @b Integer_Cmp_Int
     *
     * @param self
     * @param cmp
     * @return true
     * @return false
     */
    friend bool operator==(const Integer& self, const int& cmp) {
        if (self.upper_lim_flag || self.lower_lim_flag) {
            return false;
        }
        return self.value == cmp;
    }
    friend bool operator!=(const Integer& self, const int& cmp) {
        return self != cmp;
    }
    friend bool operator>(const Integer& self, const int& cmp) {
        if (self.upper_lim_flag) {
            return true;
        }
        if (self.lower_lim_flag) {
            return false;
        }
        return self.value > cmp;
    }
    friend bool operator<(const Integer& self, const int& cmp) {
        if (self.upper_lim_flag) {
            return false;
        }
        if (self.lower_lim_flag) {
            return true;
        }
        return self.value < cmp;
    }
    friend bool operator>=(const Integer& self, const int& cmp) {
        return !(self < cmp);
    }
    friend bool operator<=(const Integer& self, const int& cmp) {
        return !(self > cmp);
    }

    /**
     * @brief @b Int_Cmp_Integer
     *
     * @param cmp
     * @param self
     * @return true
     * @return false
     */
    friend bool operator==(const int& cmp, const Integer& self) {
        if (self.upper_lim_flag || self.lower_lim_flag) {
            return false;
        }
        return self.value == cmp;
    }
    friend bool operator!=(const int& cmp, const Integer& self) {
        return self != cmp;
    }
    friend bool operator>(const int& cmp, const Integer& self) {
        return self < cmp;
    }
    friend bool operator<(const int& cmp, const Integer& self) {
        return self > cmp;
    }
    friend bool operator>=(const int& cmp, const Integer& self) {
        return self <= cmp;
    }
    friend bool operator<=(const int& cmp, const Integer& self) {
        return self >= cmp;
    }

    /**
     * @brief @b unboxing_&_boxing
     *
     * @return @b unbox_to_int @b box_to_Integer
     */
    int unbox() {
        if (upper_lim_flag or lower_lim_flag) {
            std::cout << "You're trying to `unbox` a `LIM` Integer Object!" << std::endl;
        }
        int ret = value;
        if (upper_lim_flag) {
            ret = std::numeric_limits<int>::max();
        }
        if (lower_lim_flag) {
            ret = std::numeric_limits<int>::min();
        }
        return ret;
    }
    Integer& operator=(const int& boxing) {
        value = boxing;
        // if (boxing == std::numeric_limits<int>::max()) {
        //     upper_lim_flag = true;
        // }
        // if (boxing == std::numeric_limits<int>::min()) {
        //     lower_lim_flag = true;
        // }
        return *this;
    }
};