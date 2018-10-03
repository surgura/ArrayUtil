/*
    Compile-time size single- or multidimensional array.
*/

#pragma once

#include "CImpl.hpp"

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <array>

namespace ArrayUtil {

template <typename Element, size_t... dimensionSizes>
class CArrayData;

template <typename Element, size_t arraySize>
class CArrayData<Element, arraySize>
{
    std::array<Element, arraySize> data;
    // TODO
    
    template <std::size_t... Is>
    CArrayData(std::initializer_list<Element> const& values, std::index_sequence<Is...>) :
        data({*(values.begin() + Is)...}) {}
public:
    CArrayData(std::initializer_list<Element> const& values) :
        CArrayData(values, std::make_index_sequence<arraySize>())
    {}
};

// workaround because some compilers don't understand fold expressions in template parameters
namespace CArrayDataInternal {
    template <size_t... values>
    struct TemplateSum
    {
        static constexpr size_t sum = (values*...);
    };
}
// Array that is the right size to hold the given multidimensional array
template <typename Element, size_t... dimensionSizes>
using MultiArrayData = CArrayData<Element, CArrayDataInternal::TemplateSum<dimensionSizes...>::sum>;

template <typename Element, size_t... dimensionSizes>
class CArrayData
{
    MultiArrayData<Element, dimensionSizes...> data;
public:
    // TODO
};

template <typename Element, size_t... dimensionSizes>
class CArray : public CImpl<CArrayData<Element, dimensionSizes...>, Element, dimensionSizes...>
{
    using CImpl<CArrayData<Element, dimensionSizes...>, Element, dimensionSizes...>::CImpl;
};

template <typename Element, size_t arraySize>
class CArray<Element, arraySize> : public CImpl<CArrayData<Element, arraySize>, Element, arraySize>
{
public:
    using CImpl<CArrayData<Element, arraySize>, Element, arraySize>::CImpl;
};

}