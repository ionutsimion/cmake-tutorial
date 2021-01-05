#include <iostream>
#include <string>

#include <config.hxx>
#include <math.hxx>

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
        std::cout << "The square root of " << x << " is " << is::square_root(x) << std::endl;
    }

    return 0;
}
