#include "Utils.h"

#include <iomanip>

#include "durlib/Log/Log.h"

namespace DURLIB
{
    // int MToKM(int num)
    // {
    //     return (int)std::ceil(num / 1000);
    // }
    double MToKM(double num)
    {
        return std::ceil(num / 1000);
    }
    // float MToKM(float num)
    // {
    //     return std::ceil(num / 1000);
    // }
}