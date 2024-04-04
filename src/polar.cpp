#include <stdexcept>
#include <math.h>

#include <polar.h>

PositiveInterval::PositiveInterval(real a, real b) : min(a), max(b)
{
    if (a < 0 || b < 0)
    {
        throw std::range_error("Negative init. for positive interval");
    }
    if (a > b)
    {
        std::swap(min, max);
    }
}

PositiveInterval::PositiveInterval(real a) : min(a), max(a) {}

PositiveInterval PositiveInterval::operator+(PositiveInterval other)
{
    return PositiveInterval(min + other.min, max + other.max);
}

PositiveInterval PositiveInterval::operator*(PositiveInterval other)
{
    return PositiveInterval(min * other.min, max * other.max);
}

RemaindedInterval::RemaindedInterval(real a, real b) : min(a), max(b)
{
    if (a < 0 || b < 0)
    {
        throw std::range_error("Negative init. for positive interval");
    }
    if (a > b)
    {
        std::swap(min, max);
    }
}

RemaindedInterval::RemaindedInterval(real a) : min(a), max(a) {}

RemaindedInterval RemaindedInterval::operator+(RemaindedInterval other)
{
    auto r = RemaindedInterval(min + other.min, max + other.max);
    if (remainder || other.remainder)
    {
        r.remainder = true;
        r.set_remainder();
    }
    return r;
}

RemaindedInterval RemaindedInterval::operator*(RemaindedInterval other)
{
    auto r = RemaindedInterval(min * other.min, max * other.max);
    if (remainder || other.remainder)
    {
        r.remainder = true;
        r.set_remainder();
    }
    return r;
}

void RemaindedInterval::set_remainder()
{
    if (max > 2 * M_PI)
    {
        int ratio = max / 2 * M_PI;
        max = max - 2 * M_PI * ratio;
    }
}

PolarInterval::PolarInterval(PositiveInterval mod, RemaindedInterval arg) : mod(mod), arg(arg) {}

PolarInterval PolarInterval::singleton(real modulus, real argument)
{
    if (modulus < 0)
    {
        throw std::range_error("Negative modulus in a polar interval");
    }
    if (argument < 0 || argument > 2 * M_PI || argument)
    {
        throw std::range_error("Bad argument in polar interval");
    }
    return PolarInterval(PositiveInterval(modulus), RemaindedInterval(argument));
}

PolarInterval PolarInterval::operator*(PolarInterval other)
{
    return PolarInterval(mod * other.mod, arg + other.arg);
}
