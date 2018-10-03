/*
    Compile-time size single- or multidimensional view over an array.
*/

#pragma once

#include <cstddef>

namespace ArrayUtil {

template <typename Element, size_t... view_sizes>
class CView
{
    // TODO
};

template <typename Element, size_t view_size>
class CView<Element, view_size>
{
    Element* _data;

public:
    CView(Element* data) :
        _data(data)
    {}

    template <typename Owner>
    CView(Owner& owner) :
        _data(owner.data())
    {}

    using iterator = Element*;

    Element* data() const
    {
        return _data;
    }

    Element* data()
    {
        return _data;
    }

    static constexpr std::size_t size()
    {
        return view_size; 
    }

    iterator begin() const
    {
        return _data;
    }

    iterator begin()
    {
        return _data;
    }

    iterator end() const
    {
        return _data + size();
    }

    iterator end()
    {
        return _data + size();
    }
};

}