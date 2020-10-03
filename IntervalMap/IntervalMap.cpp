
#include "IntervalMap.h"

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";

    auto map = interval_map<unsigned, char>('A');
    map.assign(3, 5, 'B');
    map.assign(5, 7, 'B');
    map.assign(5, 7, 'C');
    map.assign(1, 7, 'A');
    map.assign(10, 7, 'D');
    map.assign(10, 15, 'D');

    for (auto i = 0; i < 20; ++i)
    {
        std::cout << "Key, Value: " << i << ", " << map[i] << "\n";
    }
}
