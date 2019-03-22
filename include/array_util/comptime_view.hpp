#ifndef ARRAY_UTIL_COMPTIME_VIEW
#define ARRAY_UTIL_COMPTIME_VIEW

#include "comptime_base.hpp"

namespace array_util {

namespace detail {

    template<typename element, std::size_t... dimension_sizes>
    class comptime_view_data
    {
        element* _data;
    protected:
        element* data() { return _data; }
    public:
        comptime_view_data(element* data) :
            _data(data)
        {}
    };

}

template<typename element, std::size_t... dimension_sizes>
class comptime_view : public detail::comptime_base<detail::comptime_view_data<element, dimension_sizes...>, element, dimension_sizes...>
{
public:
    using detail::comptime_base<detail::comptime_view_data<element, dimension_sizes...>, element, dimension_sizes...>::comptime_base;
};

}

#endif