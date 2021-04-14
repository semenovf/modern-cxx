#pragma once

#include "constexpr_map.h"

#include <type_traits>

template <typename T>
constexpr void Swap (T & a, T & b)
{
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

template<class K, class V, int S>
constexpr auto Sort(ConstexprMap<K, V, S> map) {

    auto size = map.Size();

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {

            bool need_exchange = false;

            if constexpr (std::is_integral_v<K>) {
                need_exchange = map.GetByIndex(j + 1).first > map.GetByIndex(j).first;
            } else {
                need_exchange = map.GetByIndex(j + 1).first < map.GetByIndex(j).first;
            }

            if (need_exchange) {
                auto & a = map.GetByIndex(j);
                auto & b = map.GetByIndex(j + 1);

                Swap(a.first, b.first);
                Swap(a.second, b.second);
            }
        }
    }

    return map;
}
