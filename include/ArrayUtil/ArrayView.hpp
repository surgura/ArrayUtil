#pragma once

#include <cstddef>

namespace ArrayUtil {

template <typename Element, size_t view_size = 0>
class ArrayView
{
protected:
    Element* _data;

public:
    ArrayView(Element* data) :
        _data(data)
    {}

    template <typename Owner>
    ArrayView(Owner& owner) :
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

template <typename Element>
class ArrayView<Element,0>
{
protected:
    Element* _data;
    size_t _size;

public:
    ArrayView(Element* data, size_t size) :
        _data(data),
        _size(size)
    {}

    template <typename Owner>
    ArrayView(Owner& owner) :
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