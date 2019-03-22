#include "array_util/base.hpp"
#include <array>
#include <iostream>

class tmpdata
{
    std::array<int, 3> dat = {1,2,3};
protected:
    int* data() { return dat.data(); }
};

int main()
{
    static_base<tmpdata, int, 2> impl;
    int x = impl.at(0);
    std::cout << x << std::endl;

    for (int& i : impl)
    {
        std::cout << i << std::endl;
    }

    return 0;
}