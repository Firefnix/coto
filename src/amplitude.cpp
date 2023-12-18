#include <stdexcept>
#include <amplitude.h>
#include <cmath>
#include <numeric>
#include <iostream>
#include <cstdlib>
#include <ctime>

ampl::Amplitude ampl::random()
{
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float i = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return ampl::Amplitude(r, i);
}

std::size_t ampl::pow2(std::size_t n)
{
    switch (n)
    {
    case 0:
        return 1;
    case 1:
        return 2;
    default:
        std::size_t a = ampl::pow2(n / 2);
        if (n % 2 == 0)
        {
            return a * a;
        }
        return 2 * a * a;
    }
}
