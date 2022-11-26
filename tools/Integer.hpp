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
    int  value             = 0;
    bool positive_infinity = false;
    bool negative_infinity = false;

    /**
     * @brief Construct a new Integer object
     *
     * @param value
     */
    explicit Integer(int value)
        : value(value) { }

    /// @brief default constructor
    Integer() = default;

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
        value             = copied.value;
        positive_infinity = copied.positive_infinity;
        negative_infinity = copied.negative_infinity;
        return *this;
    }

    /**
     * @brief Move a new Integer object
     *
     * @param moved
     */
    Integer(Integer&& moved) noexcept
        : value(moved.value)
        , positive_infinity(moved.positive_infinity)
        , negative_infinity(moved.negative_infinity) {
    }
    Integer& operator=(Integer&& moved) noexcept {
        value             = moved.value;
        positive_infinity = moved.positive_infinity;
        negative_infinity = moved.negative_infinity;
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

        bool if_this_upper_lim    = this->positive_infinity;
        bool if_this_lower_lim    = this->negative_infinity;
        bool if_another_upper_lim = another.positive_infinity;
        bool if_another_lower_lim = another.negative_infinity;
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

        bool if_this_upper_lim    = this->positive_infinity;
        bool if_this_lower_lim    = this->negative_infinity;
        bool if_another_upper_lim = another.positive_infinity;
        bool if_another_lower_lim = another.negative_infinity;
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

        bool if_this_upper_lim    = this->positive_infinity;
        bool if_this_lower_lim    = this->negative_infinity;
        bool if_another_upper_lim = another.positive_infinity;
        bool if_another_lower_lim = another.negative_infinity;
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
        if (self.positive_infinity || self.negative_infinity) {
            return false;
        }
        return self.value == cmp;
    }
    friend bool operator!=(const Integer& self, const int& cmp) {
        return self != cmp;
    }
    friend bool operator>(const Integer& self, const int& cmp) {
        if (self.positive_infinity) {
            return true;
        }
        if (self.negative_infinity) {
            return false;
        }
        return self.value > cmp;
    }
    friend bool operator<(const Integer& self, const int& cmp) {
        if (self.positive_infinity) {
            return false;
        }
        if (self.negative_infinity) {
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
        if (self.positive_infinity || self.negative_infinity) {
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
        if (positive_infinity or negative_infinity) {
            std::cout << "You're trying to `unbox` a `LIM` Integer Object!" << std::endl;
        }
        int ret = value;
        if (positive_infinity) {
            ret = std::numeric_limits<int>::max();
        }
        if (negative_infinity) {
            ret = std::numeric_limits<int>::min();
        }
        return ret;
    }
    Integer& operator=(const int& boxing) {
        value = boxing;
        return *this;
    }

    /**
     * @brief calculations
     *
     */
    friend Integer operator+(
        const Integer& lhs,
        const Integer& rhs
    ) {
        Integer ret;
        ret.value               = lhs.value + rhs.value;
        bool l_pos_r_neg        = lhs.positive_infinity and rhs.negative_infinity;
        bool r_pos_l_neg        = rhs.positive_infinity and lhs.negative_infinity;
        bool if_pos_and_neg_inf = l_pos_r_neg or r_pos_l_neg;
        if (if_pos_and_neg_inf) {
            ret.value = 0;
        } else {
            if (lhs.positive_infinity or rhs.positive_infinity) {
                ret.positive_infinity = true;
            }
            if (lhs.negative_infinity or rhs.negative_infinity) {
                ret.negative_infinity = true;
            }
        }
        return ret;
    }
};