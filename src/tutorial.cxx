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
#if defined(HAVE_LOG) && defined(HAVE_EXP)
        std::cout << "Using exp end log to compute the square root" << std::endl;
#endif
        std::cout << "The square root of " << x << " is " <<
#ifdef USE_CUSTOM_MATH
#   if defined(HAVE_LOG) && defined(HAVE_EXP)
            square_root(x)
#   else
            quake_reverse_square_root(x)
#   endif
#else
            std::sqrt(x)
#endif
            << std::endl;
    }

    return 0;
}
