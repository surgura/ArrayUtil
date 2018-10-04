// TODO descr

#pragma once

#include <cstddef>

namespace ArrayUtil {

// TODO we use implementation, so should include somewhere (circular dependency)
template <typename Element, size_t... viewSizes>
class CView;

template <typename Data, typename Element, size_t... view_sizes>
class CImpl : public Data
{
    template<typename As, std::size_t>
    using as = As;

    template<size_t head, size_t... tail>
    using CViewMinusOneImpl = CView<Element, tail...>;
    using CViewMinusOne = CViewMinusOneImpl<view_sizes>;

    template<size_t head, size_t... tail>
    static constexpr size_t SubViewOffset(size_t index)
    {
        return index*(tail*...);
    }
public:
    using Data::Data;

    Element* data() const
    {
        return _data;
    }

    Element* data()
    {
        return _data;
    }

    CViewMinusOne At(size_t index)
    {
        return CViewMinusOne(_data + SubViewOffset<view_sizes...>(index)); // TODO offset
    }

private:
    template <typename head, typename... tail>
    Element& AtImpl(head, tail...)
    {
        At(head).At(tail...);
    }
public:

    Element& At(as<size_t, view_sizes>... indices)
    {
        AtImpl(indices...);
    }
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

    Element& At(size_t index)
    {
        return *(begin() + index);
    }

    Element& At(size_t index) const
    {
        return *(begin() + index);
    }
};

}