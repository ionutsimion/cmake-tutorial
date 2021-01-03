#include <fstream>
#include <cmath>

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    std::ofstream os(argv[1], std::ios_base::out);
    if (os.is_open())
    {
        os << "double sqrt_table[]{ ";
        for (auto i = 0; i < 10; ++i)
            os << sqrt(static_cast<double>(i)) << ", ";
        os << "0 };" << std::endl;
        os.close();

        return 0;
    }

    return 1;
}
