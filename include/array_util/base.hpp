#ifndef ARRAY_UTIL_BASE_HPP
#define ARRAY_UTIL_BASE_HPP

#include <cstdint>
#include <type_traits>

template<typename element, std::size_t... dimension_sizes>
class static_view
{
    element* data;
public:
    static_view(element* data) :
        data(data) {}
};

template<typename data, typename element, std::size_t dimension_sizes_head, std::size_t... dimension_sizes_tail>
class static_base : protected data
{
public:
    // TODO currently iterating only works for 1D
    using iterator = element*;

    // If 1D: Get element
    // If nD: Get subview in lowest dimension
    auto at(std::size_t index)
    {
        // if tail is empty, we are 1D.
        if constexpr(sizeof...(dimension_sizes_tail) == 0)
        {
            return *(data::data() + index);
        }
        else
        {
            return static_view<element, dimension_sizes_tail...>(
                data::data() + index*(dimension_sizes_tail*...)
            );
        }
    }

    auto at(std::size_t index) const
    {
        // if tail is empty, we are 1D.
        if constexpr(sizeof...(dimension_sizes_tail) == 0)
        {
            return *(data::data() + index);
        }
        else
        {
            return static_view<element, dimension_sizes_tail...>(
                data::data() + index*(dimension_sizes_tail*...)
            );
        }
    }

    // If 1D: Iterate over elements
    // If nD: Iterate over subviews in lowest dimension
    iterator begin()
    {
        return data::data();
    }

    iterator begin() const
    {
        return data::data();
    }

    iterator end()
    {
        // if tail is empty, we are 1D.
        if constexpr(sizeof...(dimension_sizes_tail) == 0)
        {
            return data::data() + dimension_sizes_head;
        }
        else
        {
            return data::data() + dimension_sizes_head*(dimension_sizes_tail*...);   
        }
    }

    iterator end() const
    {
        // if tail is empty, we are 1D.
        if constexpr(sizeof...(dimension_sizes_tail) == 0)
        {
            return data::data() + dimension_sizes_head;
        }
        else
        {
            return data::data() + dimension_sizes_head*(dimension_sizes_tail*...);   
        }
    }
};

#endif