#include "ArrayUtil/CView.hpp"

#include <array>
#include <cstdint>
#include <iostream>

using namespace ArrayUtil;

static constexpr size_t testSize = 3;

template <typename T, typename Owner>
bool RunTests(std::string const& testName, T& view, Owner& owner)
{
    // check data
    if (!(owner[0] == *view.begin() && owner[1] == *(view.begin()+1) && owner[2] == *(view.begin()+2)))
    {
        std::cout << "!!! FAIL !!!" << std::endl;
        std::cout << "In test '" << testName.c_str() << "':" << std::endl;
        std::cout << "Viewed data incorrect" << std::endl;
        return false;
    }

    // begin & end, const

    // Range-based for loop (just check if it compiles)
    for (auto const& el : view) {}

    return true;
}

int main()
{
    bool success = true;

    std::array<uint32_t, testSize> testArrayMut{1,2,3};

    // Compile time size + initialize from pointer + mutable
    {
        CView<uint32_t, testSize> view(testArrayMut.data());
        success &= RunTests("Compile time size + initialize from pointer + mutable", view, testArrayMut);
    }

    // Compile time size + initialize from object + mutable
    {
        CView<uint32_t, testSize> view(testArrayMut);
        success &= RunTests("Compile time size + initialize from object + mutable", view, testArrayMut);
    }

    std::array<uint32_t, testSize> testArrayConst{1,2,3};

    // Compile time size + initialize from pointer + const
    {
        CView<uint32_t, testSize> view(testArrayConst.data());
        success &= RunTests("Compile time size + initialize from pointer + const", view, testArrayConst);
    }

    // Compile time size + initialize from object + const
    {
        CView<uint32_t, testSize> view(testArrayConst);
        success &= RunTests("Compile time size + initialize from object + const", view, testArrayConst);
    }

    if (success)
        std::cout << "Everything works!" << std::endl;
    else
        std::cout << "Some tests failed!" << std::endl;

    return 0;
}