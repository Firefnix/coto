#include <stdexcept>
#include <absi/polar.h>

using namespace polar;

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

PositiveInterval polar::PositiveInterval::operator|(PositiveInterval other)
{
    return PositiveInterval(std::min(min, other.min), std::max(max, other.max));
}

AngleInterval::AngleInterval(real min, real delta) : min(min), delta(delta)
{
    if (delta < 0)
    {
        throw std::range_error("Negative delta for angle interval");
    }
    if (min > 2 * pi || min < 0)
    {
        int ratio = min / 2 * pi;
        min = min - 2 * pi * ratio;
    }
    if (delta > 2 * pi)
    {
        delta = 2 * pi;
    }
}

AngleInterval::AngleInterval(real min) : min(min), delta(0.) {}

AngleInterval polar::AngleInterval::min_max(real a, real b)
{
    return AngleInterval(std::min(a, b), std::abs(a - b));
}

AngleInterval AngleInterval::operator+(AngleInterval other)
{
    auto r = AngleInterval(min + other.min, delta + other.delta);
    r.set_remainder();
    return r;
}

AngleInterval AngleInterval::operator*(AngleInterval other)
{
    auto r = AngleInterval(std::min(min * other.min, (min + delta) * (other.min + other.delta)), delta * other.delta);
    r.set_remainder();
    return r;
}

AngleInterval polar::AngleInterval::operator|(AngleInterval other)
{
    return AngleInterval::min_max(std::min(min, other.min), std::max(min + delta, other.min + other.delta));
}

void AngleInterval::set_remainder()
{
    if (min > 2 * pi || min < 0)
    {
        int ratio = min / 2 * pi;
        min = min - 2 * pi * ratio;
    }
    if (delta > 2 * pi)
    {
        delta = 2 * pi;
    }
}

Interval::Interval(PositiveInterval mod, AngleInterval arg) : mod(mod), arg(arg) {}

Interval Interval::singleton(real modulus, real argument)
{
    if (modulus < 0)
    {
        throw std::range_error("Negative modulus in a polar interval");
    }
    if (argument < 0 || argument > 2 * pi)
    {
        throw std::range_error("Bad argument in polar interval");
    }
    return Interval(PositiveInterval(modulus), AngleInterval(argument));
}

Interval Interval::operator*(Interval other)
{
    return Interval(mod * other.mod, arg + other.arg);
}

Interval polar::Interval::operator|(Interval other)
{
    return Interval(mod | other.mod, arg | other.arg);
}
