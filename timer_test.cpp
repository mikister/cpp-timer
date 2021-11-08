#include <iostream>
#include <chrono>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "timer.hpp"

void check(std::string test_name, const bool condition)
{
    std::cout << std::move(test_name);
    if (condition)
    {
        std::cout << "-> PASSED!\n";
    }
    else
    {
        std::cout << "-> FAILED!\n";
    }
}

void check_add_tag()
{
    timer_util::timer timer;
    timer.add_tag("test");
    check("Check adding tags...", timer.tags[0].name == "test");
}

void check_to_string()
{
    timer_util::timer timer;

    timer.add_tag("tag 1");
    sleep(0.5);
    timer.add_tag("tag 2");
    sleep(0.5);
    timer.add_tag("tag 3");

    std::string expectedString = "";
    expectedString += "tag 1: ";
    expectedString += std::to_string(((std::chrono::duration<double, std::milli>)(timer.tags[0].time_point - timer.tags[0].time_point)).count());
    expectedString += "ms\n";
    expectedString += "tag 2: ";
    expectedString += std::to_string(((std::chrono::duration<double, std::milli>)(timer.tags[1].time_point - timer.tags[0].time_point)).count());
    expectedString += "ms\n";
    expectedString += "tag 3: ";
    expectedString += std::to_string(((std::chrono::duration<double, std::milli>)(timer.tags[2].time_point - timer.tags[1].time_point)).count());
    expectedString += "ms\n";

    check("Check formating data into a string...", timer.to_string() == expectedString);
}

void stress_test()
{
    timer_util::timer timer;
    std::uint_fast32_t insertion_count = 1000000;
    auto start = std::chrono::high_resolution_clock::now();

    for (std::uint_fast32_t i = 0; i < insertion_count; i++)
    {
        timer.add_tag("test");
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> required_time = end - start;

    std::cout << "Performed " << insertion_count << " time point recordings.\n";
    std::cout << "Time required: " << required_time.count() << "ms.\n";
    std::cout << "Averages to " << required_time.count() / insertion_count << "ms per recording.\n";
}

int main()
{
    check_add_tag();
    check_to_string();
    stress_test();
}