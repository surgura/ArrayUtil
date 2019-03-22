#include "array_util/comptime_view.hpp"
#include <array>
#include <iostream>
#include "array_util/comptime_array.hpp"
#include <functional>

int main()
{
    std::array<int, 3> dat = {1,2,3};

    {
        array_util::comptime_view<int, 3> view(dat.data());
        int& x = view.at(0);
        std::cout << x << std::endl;

        for (int& i : view)
        {
            std::cout << i << std::endl;
        }
    }

    {
        array_util::comptime_array<int, 3> array;
        int& x = array.at(0);
        x = 1500;
        std::cout << x << std::endl;

        for (int& i : array)
        {
            std::cout << i << std::endl;
        }
    }

    return 0;
}