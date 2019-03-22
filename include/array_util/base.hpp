#ifndef ARRAY_UTIL_BASE_HPP
#define ARRAY_UTIL_BASE_HPP

#include <cstdint>
#include <type_traits>

template<typename element, std::size_t... dimension_sizes>
class comptime_view;

namespace array_util::detail
{

template<typename data, typename element, std::size_t dimension_sizes_head, std::size_t... dimension_sizes_tail>
class comptime_base : protected data
{
public:
    using data::data;

    // TODO currently iterating only works for 1D
    using iterator = element*;

    // If 1D: Get element
    // If nD: Get subview in lowest dimension
    decltype(auto) at(std::size_t index)
    {
        // if tail is empty, we are 1D.
        if constexpr(sizeof...(dimension_sizes_tail) == 0)
        {
            return (data::data()[index]);
        }
        else
        {
            return comptime_view<element, dimension_sizes_tail...>(
                data::data() + index*(dimension_sizes_tail*...)
            );
        }
    }

    decltype(auto) at(std::size_t index) const
    {
        // if tail is empty, we are 1D.
        if constexpr(sizeof...(dimension_sizes_tail) == 0)
        {
            return (data::data()[index]);
        }
        else
        {
            return comptime_view<element, dimension_sizes_tail...>(
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

}

#endif