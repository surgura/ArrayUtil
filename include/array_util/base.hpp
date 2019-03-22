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
};

#endif