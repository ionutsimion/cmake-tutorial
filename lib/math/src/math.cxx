#include <cstdint>
#include <cmath>

#include <math.hxx>

namespace is
{
    inline double exp_log_square_root(double const x)
    {
        return exp(log(x) * 0.5);
    }

    inline float quake_reverse_square_root(float const x)
    {
        const auto three_halfs{ 1.5f };
        auto half_x{ x * 0.5f };
        auto i{ *reinterpret_cast<int32_t *>(const_cast<float *>(&x)) };
        i = 0x5f3759df - (i >> 1);
        auto y{ *reinterpret_cast<float *>(&i) };
        y *= three_halfs - (half_x * y * y);
        
        return 1.0f / (y * (three_halfs - (half_x * y * y)));
    }
    
    double square_root(double const x)
    {
#if defined(HAVE_LOG) and defined(HAVE_EXP)
        return exp_log_square_root(x);
#endif
        return quake_reverse_square_root(x);
    }
}
