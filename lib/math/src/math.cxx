#include <cstdint>
#include <cmath>

#include <iostream>

#include <math.hxx>
#include <table.hxx>

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

    inline double square_root_from_table(double const x)
    {
        auto f{ sqrt_table[static_cast<int>(x)] };

        // do 10 iterations
        for (auto i = 0; i < 10; ++i)
        {
            if (f <= 0)
                f = 0.1;
            auto const delta = x - (f * f);
            f += 0.5 * delta / f;
        }

        return f;
    }
    
    double square_root(double const x)
    {
        if (x <= 0.0)
            return 0;

#if defined(HAVE_LOG) and defined(HAVE_EXP)
        if (x < 10)
        {
            std::cout << "Using the square roots table..." << std::endl;
            return square_root_from_table(x);
        }
        return exp_log_square_root(x);
#endif
        return quake_reverse_square_root(x);
    }
}
