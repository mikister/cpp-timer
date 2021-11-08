# timer_util::timer

A C++ utility for recording and formatting time point data.

## Usage

To use in project just include the header file `timer.hpp`.

To record a time point:

```cpp
timer_util::timer timer;
timer.add_tag("tag name");
```

To get a formated string:

```cpp
std::cout << timer.to_string();
```

## Example

```cpp
#include <iostream> // std::cout
#ifdef _WIN32
#include <Windows.h> // sleep
#else
#include <unistd.h> // sleep
#endif

#include "timer.hpp"

int main()
{
    timer_util::timer timer;

    timer.add_tag("tag 1");
    sleep(2);
    timer.add_tag("tag 2");
    sleep(1);
    timer.add_tag("tag 3");

    std::cout << timer.to_string();

    return 0;
}
```

Which will print something similar to:

```
tag 1: 0.000000ms
tag 2: 2000.100213ms
tag 3: 1000.100112ms
```
