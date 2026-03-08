#pragma once

#include<cmath>
#include<type_traits>

namespace extraFunc{ // Extra functions. Use for compute in other functions.
    template<typename T, typename = std::enable_if_t<std::is_integral_v<T>, T>>
    T pow(T a, size_t b, size_t mod = 1) {
        if (!a) return 0;
        T res = 1;
        while (b > 0) {
            if (b & 1) res = ((res % mod) * (a % mod)) % mod;
            a = ((a % mod) * (a % mod)) % mod;
            b >>= 1;
        }
        return res;
    } 
    template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>, T>>
    T pow(T a, size_t b, long double eps = 1e-9) {
        if (std::abs(a) < eps) return 0.0;
        T res = 1.0;
        while (b > 0) {
            if (b & 1) res = res * a;
            a = a * a;
            b >>= 1;
        }
        if (std::abs(a) < eps) return 0.0;
        return res;
    }
};