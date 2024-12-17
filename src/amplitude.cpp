#include <amplitude.h>
#include <array>

std::string ampl::to_string(const ampl::Amplitude a)
{
    if (!a.imag()) {
        return std::to_string(a.real());
    }
    if (!a.real()) {
        return std::to_string(a.imag());
    }
    return std::to_string(a.real()) + "+" + std::to_string(a.imag()) + "i";
}

ampl::Amplitude ampl::random()
{
    Amplitude a;
    do {
        real r = static_cast<real>(rand()) / static_cast<real>(RAND_MAX);
        real i = static_cast<real>(rand()) / static_cast<real>(RAND_MAX);
        a = ampl::Amplitude(r, i);
    } while (abs(a) > 1);
    return a;
}
