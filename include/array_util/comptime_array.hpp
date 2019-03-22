#ifndef ARRAY_UTIL_COMPTIME_ARRAY
#define ARRAY_UTIL_COMPTIME_ARRAY

#include "comptime_base.hpp"
#include <array>

namespace array_util {

namespace detail {

    template<typename element, std::size_t... dimension_sizes>
    class comptime_array_data
    {
        std::array<element, (dimension_sizes*...)> _data;
    protected:
        element* data() { return _data.data(); }
    };

}

template<typename element, std::size_t... dimension_sizes>
class comptime_array : public detail::comptime_base<detail::comptime_array_data<element, dimension_sizes...>, element, dimension_sizes...>
{
public:
    using detail::comptime_base<detail::comptime_array_data<element, dimension_sizes...>, element, dimension_sizes...>::comptime_base;
};

}

#endif