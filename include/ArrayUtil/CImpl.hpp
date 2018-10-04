// TODO descr

#pragma once

#include <cstddef>

namespace ArrayUtil {

// TODO we use implementation, so should include somewhere (circular dependency)
template <typename Element, size_t... viewSizes>
class CView;

template <typename Data, typename Element, size_t... viewSizes>
class CImpl : public Data
{
    template<typename As, std::size_t>
    using as = As;

    template <size_t head, size_t... tail>
    struct CViewMinusOneImpl { using type = CView<Element, tail...>; };
    using CViewMinusOne = typename CViewMinusOneImpl<viewSizes...>::type;

    template<size_t head, size_t... tail>
    static constexpr size_t SubViewOffset(size_t index)
    {
        return index*(tail*...);
    }
public:
    using Data::Data;

    Element* data() const
    {
        return Data::_data;
    }

    Element* data()
    {
        return Data::_data;
    }

    CViewMinusOne At(size_t index)
    {
        return CViewMinusOne(data() + SubViewOffset<viewSizes...>(index)); // TODO offset
    }

    CViewMinusOne At(size_t index) const
    {
        return CViewMinusOne(data() + SubViewOffset<viewSizes...>(index)); // TODO offset
    }

private:
    template <typename Head, typename... Tail>
    Element& AtImpl(Head head, Tail... tail)
    {
        return At(head);//.At(tail...);
    }

    template <typename Head, typename... Tail>
    Element& AtImpl(Head head, Tail... tail) const
    {
        return At(head);//.At(tail...);
    }
public:

    Element& At(as<size_t, viewSizes>... indices)
    {
        AtImpl(indices...);
    }

    Element& At(as<size_t, viewSizes>... indices) const
    {
        AtImpl(indices...);
    }

    CViewMinusOne operator[](size_t index)
    {
        return At(index);
    }

    CViewMinusOne operator[](size_t index) const
    {
        return At(index);
    }
};

template <typename Data, typename Element, size_t viewSize>
class CImpl<Data, Element, viewSize> : public Data
{
public:
    using Data::Data;

    using iterator = Element*;

    Element* data() const
    {
        return Data::_data;
    }

    Element* data()
    {
        return Data::_data;
    }

    static constexpr std::size_t size()
    {
        return viewSize; 
    }

    iterator begin() const
    {
        return data();
    }

    iterator begin()
    {
        return data();
    }

    iterator end() const
    {
        return data() + size();
    }

    iterator end()
    {
        return data() + size();
    }

    Element& At(size_t index)
    {
        return *(begin() + index);
    }

    Element& At(size_t index) const
    {
        return *(begin() + index);
    }

    Element& operator[](size_t index)
    {
        return At(index);
    }

    Element& operator[](size_t index) const
    {
        return At(index);
    }
};

}