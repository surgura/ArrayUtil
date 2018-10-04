#include "ArrayUtil/CView.hpp"
#include "ArrayUtil/CArray.hpp"

#include <array>
#include <cstdint>
#include <iostream>

using namespace ArrayUtil;

static constexpr size_t testSize = 3;

template <typename T, typename Owner>
bool RunTests(std::string const& testName, T& view, Owner& owner)
{
    // check size
    if (view.size() != owner.size())
    {
        std::cout << "!!! FAIL !!!" << std::endl;
        std::cout << "In test '" << testName.c_str() << "':" << std::endl;
        std::cout << "Sizes don't match" << std::endl;
        return false;
    }

    // check data & array access
    if (!(owner[0] == view[0] && owner[1] == view[1] && owner[2] == view[2]))
    {
        std::cout << "!!! FAIL !!!" << std::endl;
        std::cout << "In test '" << testName.c_str() << "':" << std::endl;
        std::cout << "Viewed data incorrect" << std::endl;
        return false;
    }

    // Range-based for loop (just check if it compiles)
    for (auto const& el : view) {}

    return true;
}

int main()
{
    bool success = true;

    {
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
    }

    {
        std::array<uint32_t, testSize> const testArrayConst{1,2,3};

        // Compile time size + initialize from pointer + const
        {
            CView<uint32_t const, testSize> view(testArrayConst.data());
            success &= RunTests("Compile time size + initialize from pointer + const", view, testArrayConst);
        }

        // Compile time size + initialize from object + const
        {
            CView<uint32_t const, testSize> view(testArrayConst);
            success &= RunTests("Compile time size + initialize from object + const", view, testArrayConst);
        }

        {
            std::array<uint32_t, testSize> testArray{1,2,3};
            CArray<uint32_t, testSize> cArray{1,2,3};
            success &= RunTests("CArray + Compile time size", cArray, testArray);
        }
    }

    {
        std::array<uint32_t, testSize> testArray{1,2,3};
        CArray<uint32_t const, testSize> cArray{1,2,3};
        success &= RunTests("CArray + Compile time size + const", cArray, testArray);
    }

    if (success)
        std::cout << "Everything works!" << std::endl;
    else
        std::cout << "Some tests failed!" << std::endl;

    return 0;
}