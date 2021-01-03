#include <cstdint>
#include <cmath>

#include <iostream>

#include <config.hxx>
#include <math.hxx>

namespace is
{
#if defined(HAVE_LOG) && defined(HAVE_EXP)
    double square_root(double const x)
    {
        return exp(log(x) * 0.5);
    }
#endif

    float quake_reverse_square_root(float const x)
    {
        const auto three_halfs{ 1.5f };
        auto half_x{ x * 0.5f };
        auto i{ *reinterpret_cast<int32_t *>(const_cast<float *>(&x)) };
        i = 0x5f3759df - (i >> 1);
        auto y{ *reinterpret_cast<float *>(&i) };
        y *= three_halfs - (half_x * y * y);
        
        return 1.0f / (y * (three_halfs - (half_x * y * y)));
    }
}
