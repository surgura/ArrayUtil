/*
    Compile-time size single- or multidimensional array.
*/

// TODO constructor takes initializer list, but this can be smaller than data size. verify size or something at compile time

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
protected:
    std::array<Element, arraySize> _data;
private:
    template <std::size_t... Is>
    CArrayData(std::initializer_list<Element> const& values, std::index_sequence<Is...>) :
        _data({*(values.begin() + Is)...}) {}
public:
    CArrayData(std::initializer_list<Element> const& values) :
        CArrayData(values, std::make_index_sequence<arraySize>())
    {
    }

    Element* data() const
    {
        return _data.data();
    }

    Element* data()
    {
        return _data.data();
    }
};

// workaround because some compilers don't understand fold expressions in template parameters
namespace CArrayDataInternal {
    template <size_t head, size_t... tail>
    struct TemplateSum
    {
        static constexpr size_t sum = head*TemplateSum<tail...>::sum;
    };
    template <size_t head>
    struct TemplateSum<head>
    {
        static constexpr size_t sum = head;
    };
}
// Array that is the right size to hold the given multidimensional array
template <typename Element, size_t... dimensionSizes>
using MultiArrayData = CArrayData<Element, CArrayDataInternal::TemplateSum<dimensionSizes...>::sum>;

template <typename Element, size_t... dimensionSizes>
class CArrayData
{
protected:
    MultiArrayData<Element, dimensionSizes...> _data;
private:
    template <std::size_t... Is>
    CArrayData(std::initializer_list<Element> const& values, std::index_sequence<Is...>) :
        _data({*(values.begin() + Is)...}) {}
public:
    CArrayData(std::initializer_list<Element> const& values) :
        CArrayData(values, std::make_index_sequence<CArrayDataInternal::TemplateSum<dimensionSizes...>::sum>())
    {}

    Element* data() const
    {
        return _data.data();
    }

    Element* data()
    {
        return _data.data();
    }

    // TODO nested initializer list constructor
};

template <typename Element, size_t... dimensionSizes>
class CArray : public CImpl<CArrayData<Element, dimensionSizes...>, Element, dimensionSizes...>
{
public:
    using CImpl<CArrayData<Element, dimensionSizes...>, Element, dimensionSizes...>::CImpl;
};

template <typename Element, size_t arraySize>
class CArray<Element, arraySize> : public CImpl<CArrayData<Element, arraySize>, Element, arraySize>
{
public:
    using CImpl<CArrayData<Element, arraySize>, Element, arraySize>::CImpl;
};

}