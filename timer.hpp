#pragma once

/**
 * @file timer.hpp
 * @author Milan Radojević (mikister2012@gmail.com) (https://github.com/mikister)
 * @version 1.0.0
 * @date 2021-11-08
 * @brief A C++ timer util for capturing and formatting time point data.
 */

#include <chrono>  // std::chrono::_V2::system_clock::time_point, std::chrono::high_resolution_clock::now
#include <memory>  // std::move
#include <sstream> // std::stringstream
#include <string>  // std::string, std::to_string
#include <vector>  // std::vector

namespace timer_util
{
    /**
     * @brief A wrapper for recorded time data.
     *
     * @param name Name of time point. Used in formatting.
     * @param time_point Time data to be recorded.
     */
    struct tag
    {
        std::string name;
        std::chrono::_V2::system_clock::time_point time_point;
    };

    /**
     * @brief A timer util for capturing and formatting timing data.
     */
    class timer
    {

    public:
        timer() {}
        ~timer() {}

        /**
         * @brief Vector containing the time point data.
         */
        std::vector<tag> tags;

        /**
         * @param tag_name Name for this time point. Used when formatting data.
         */
        void add_tag(std::string tag_name)
        {
            auto tp = std::chrono::high_resolution_clock::now();
            timer_util::tag tag = timer_util::tag{std::move(tag_name), std::move(tp)};

            tags.push_back(std::move(tag));
        }

        /**
         * @return String containing time data formatted into rows.
         */
        std::string to_string()
        {
            std::string str;
            std::chrono::_V2::system_clock::time_point *prev = &tags[0].time_point;

            for (timer_util::tag &curr : tags)
            {
                str += curr.name + ": " + std::to_string(((std::chrono::duration<double, std::milli>)(curr.time_point - *prev)).count()) + "ms\n";
                prev = &curr.time_point;
            }

            return std::move(str);
        }
    };
} // namespace timer_util
