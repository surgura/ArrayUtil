/*
    Compile-time size single- or multidimensional array.
*/

#pragma once

#include <cstddef>

namespace ArrayUtil {

template <typename Element, size_t... array_sizes>
class CArray
{
    // TODO
};

template <typename Element, size_t array_size>
class CArray<Element, array_size>
{
    // TODO
};

}