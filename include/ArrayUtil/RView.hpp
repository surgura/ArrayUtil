/*
    Run-time size single- or multidimensional view over an array.
*/

#pragma once

#include <cstddef>

namespace ArrayUtil {

template <typename Element, size_t dimensions = 1>
class RView
{
    // TODO
};

template <typename Element>
class RView<Element, 1>
{
protected:
    Element* _data;
    size_t _size;

public:
    RView(Element* data, size_t size) :
        _data(data),
        _size(size)
    {}

    template <typename Owner>
    RView(Owner& owner) :
        _data(owner.data()),
        _size(owner.size())
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

    std::size_t size() const
    {
        return _size; 
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