/*
    Compile-time size single- or multidimensional array.
*/

#pragma once

#include <cstddef>

namespace ArrayUtil {

template <typename Element, size_t... dimension_sizes>
class CArray;

template <typename Element, size_t array_size>
class CArray<Element, array_size>
{
    // TODO
    
public:
};

// workaround because some compilers don't understand fold expressions in template parameters
namespace CArrayInternal {
    template <size_t... values>
    struct TemplateSum
    {
        static constexpr size_t sum = (values*...);
    };
}
// Array that is the right size to hold the given multidimensional array
template <typename Element, size_t... dimension_sizes>
using MultiArrayData = CArray<Element, CArrayInternal::TemplateSum<dimension_sizes...>::sum>;

template <typename Element, size_t... dimension_sizes>
class CArray
{
    MultiArrayData<Element, dimension_sizes...> data;
public:
    // TODO
};

}