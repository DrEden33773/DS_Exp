/**
 * @file EpidemicBigData.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b CCF_202209-3
 * @version 0.1
 * @date 2022-10-12
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief
        @e user_tuple @b <date,user,region>
        @e epidemic_tuple @b <date,region> @p [date,date+7)-->epidemic_duration
 *
 */

#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
using namespace std;

class solution {
    int _days = 0;
    /**
     * @brief epidemic_info
     * @struct hashmap< date, vector<area> >
     */
    unordered_map<int, vector<int>> epidemic_info;
    /**
     * @brief _routing_msgs
     * @struct hashmap< date, vector< tuple<_date, _user, _region> > >
     */
    unordered_map<int, vector<tuple<int, int, int>>> _routing_msgs;

public:
    int input_epidemic_info(const int& date) {
        int         _warnings     = 0;
        int         _routing_msgs = 0;
        vector<int> warning_areas;
        warning_areas.reserve(_warnings);
        cin >> _warnings >> _routing_msgs;
        for (int i = 0; i < _warnings; ++i) {
            int area = 0;
            cin >> area;
            warning_areas.emplace_back(area);
        }
        epidemic_info[date] = warning_areas;
        return _routing_msgs;
    }
    void input_routing_msg(const int& date) {
    }
    void input_day() {
        cin >> _days;
        for (int date = 0; date < _days; ++date) {
            auto _routing_msgs = input_epidemic_info(date);
            for (int num = 0; num < _routing_msgs; ++num) {
                input_routing_msg(date);
            }
        }
    }
    void interface() {
        input_day();
    }
};
