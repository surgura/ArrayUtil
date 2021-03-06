#include "ArrayUtil/CView.hpp"
#include "ArrayUtil/CArray.hpp"

#include <array>
#include <cstdint>
#include <iostream>

using namespace ArrayUtil;

static constexpr size_t testSize1 = 3;
static constexpr size_t testSize2 = 2;
static constexpr size_t testSize3 = 4;

template <typename T, typename Owner>
bool RunTests(std::string const& testName, T& view, Owner& owner)
{
    auto subview1 = view.At(1);
    auto subview2 = subview1.At(1);
    uint32_t value = subview2.At(1);
    if (value != owner[1*testSize2*testSize3+1*testSize3+1])
    {
        std::cout << "!!! FAIL !!!" << std::endl;
        std::cout << "In test '" << testName.c_str() << "':" << std::endl;
        std::cout << "Values don't match" << std::endl;
        return false;
    }

    if (view[1][1][1] != owner[1*testSize2*testSize3+1*testSize3+1])
    {
        std::cout << "!!! FAIL !!!" << std::endl;
        std::cout << "In test '" << testName.c_str() << "':" << std::endl;
        std::cout << "Array index fail" << std::endl;
        return false;
    }

    return true;
}

int main()
{
    bool success = true;

    {
        std::array<uint32_t, testSize1*testSize2*testSize3> testArrayMut{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};

        // Compile time size + initialize from pointer + mutable
        {
            CView<uint32_t, testSize1, testSize2, testSize3> view(testArrayMut.data());
            success &= RunTests("CView + Compile time size + initialize from pointer + mutable", view, testArrayMut);
        }

        // Compile time size + initialize from object + mutable
        {
            CView<uint32_t, testSize1, testSize2, testSize3> view(testArrayMut);
            success &= RunTests("CView + Compile time size + initialize from object + mutable", view, testArrayMut);
        }
    }

    {
        std::array<uint32_t, testSize1*testSize2*testSize3> const testArrayConst{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};

        // Compile time size + initialize from pointer + const
        {
            CView<uint32_t const, testSize1, testSize2, testSize3> view(testArrayConst.data());
            success &= RunTests("CView + Compile time size + initialize from pointer + const", view, testArrayConst);
        }

        // Compile time size + initialize from object + const
        {
            CView<uint32_t const, testSize1, testSize2, testSize3> view(testArrayConst);
            success &= RunTests("CView + Compile time size + initialize from object + const", view, testArrayConst);
        }
    }

    {
        std::array<uint32_t, testSize1*testSize2*testSize3> testArray{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
        CArray<uint32_t, testSize1, testSize2, testSize3> cArray{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
        success &= RunTests("CArray + Compile time size", cArray, testArray);
    }

    {
        std::array<uint32_t, testSize1*testSize2*testSize3> testArray{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
        CArray<uint32_t const, testSize1, testSize2, testSize3> cArray{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
        success &= RunTests("CArray + Compile time size + const", cArray, testArray);
    }

    if (success)
        std::cout << "Everything works!" << std::endl;
    else
        std::cout << "Some tests failed!" << std::endl;

    return 0;
}
