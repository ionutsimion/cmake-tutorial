#include <iostream>
#include <string>

#include <config.hxx>

#ifdef USE_CUSTOM_MATH
#include <math.hxx>
#else
#include <cmath>
#endif

int main(int const argc, char **argv)
{
    using namespace is;

    if (argc < 2)
    {
        std::cout << argv[0]
                  << "\nCMake Tutorial v"
                  << version::major << '.' << version::minor << '.' << version::patch
                  << "\nUsage:\n\tTutorial <x>, where x is a double;\n\tReturns the square root of <x>"
                  << std::endl;
    }
    else
    {
        auto const x = std::stod(argv[1]);
#ifdef USE_CUSTOM_MATH
        auto const f = quake_reverse_square_root(x);
#else
        auto const f = std::sqrt(x);
#endif
       std::cout << "The square root of " << x << " is " << f << std::endl;
    }

    return 0;
}
