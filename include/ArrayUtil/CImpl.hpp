// TODO descr

#pragma once

#include <cstddef>

namespace ArrayUtil {

template <typename Data, typename Element, size_t... view_sizes>
class CImpl
{
    // TODO
};

template <typename Data, typename Element, size_t view_size>
class CImpl<Data, Element, view_size> : public Data
{
public:
    using Data::Data;

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