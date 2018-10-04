/*
    Compile-time size single- or multidimensional view over an array.
*/

#pragma once

#include <cstddef>
#include "CImpl.hpp"

namespace ArrayUtil {

template <typename Element, size_t... viewSizes>
class CViewData
{
protected:
    Element* _data;

public:
    CViewData(Element* data) :
        _data(data)
    {}

    template <typename Owner>
    CViewData(Owner& owner) :
        _data(owner.data())
    {}
};

template <typename Element, size_t... viewSizes>
class CView : public CImpl<CViewData<Element, viewSizes...>, Element, viewSizes...>
{
public:
    using CImpl<CViewData<Element, viewSizes...>, Element, viewSizes...>::CImpl;
};

}