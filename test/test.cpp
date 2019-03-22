#include "array_util/comptime_view.hpp"
#include <array>
#include <iostream>

int main()
{
    std::array<int, 3> dat = {1,2,3};

    array_util::comptime_view<int, 3> view(dat.data());
    int x = view.at(0);
    std::cout << x << std::endl;

    for (int& i : view)
    {
        std::cout << i << std::endl;
    }

    return 0;
}