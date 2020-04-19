#include <iostream>

#include <config.hxx>

int main(int argc, char **argv)
{
    using namespace is;

    if (argc < 2)
    {
        std::cout << argv[0]
                  << "\nCMake Tutorial v"
                  << version::major << '.' << version::minor << '.' << version::patch
                  << std::endl;
    }

    return 0;
}

