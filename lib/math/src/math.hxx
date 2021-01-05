#pragma once

#if defined(_WIN32)
#  if defined(EXPORTING_MATH)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

namespace is
{
    double DECLSPEC square_root(double);
}
