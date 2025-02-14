#include <absi/polar.h>

#include <stdexcept>
#include <numbers>
#include <iostream>

using namespace polar;

static real argument(const ampl::Amplitude &z);

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

PositiveInterval PositiveInterval::operator+(PositiveInterval &other) const
{
    return PositiveInterval(min + other.min, max + other.max);
}

PositiveInterval PositiveInterval::operator*(PositiveInterval &other) const
{
    return PositiveInterval(min * other.min, max * other.max);
}

PositiveInterval polar::PositiveInterval::operator|(PositiveInterval &other) const
{
    return PositiveInterval(std::min(min, other.min), std::max(max, other.max));
}

bool polar::PositiveInterval::operator==(const PositiveInterval &other) const
{
    return (min == other.min) && (max == other.max);
}

AngleInterval::AngleInterval(real min, real delta) : min(min), delta(delta)
{
    if (delta < 0)
    {
        throw std::range_error("Negative delta for angle interval");
    }
    if (min > 2 || min < 0)
    {
        int ratio = min / 2;
        min = min - 2 * ratio;
    }
    if (delta > 2)
    {
        delta = 2;
    }
}

AngleInterval::AngleInterval(real min) : min(min), delta(0.) {}

AngleInterval polar::AngleInterval::min_max(real a, real b)
{
    return AngleInterval(std::min(a, b), std::abs(a - b));
}

AngleInterval AngleInterval::operator+(AngleInterval &other) const
{
    auto r = AngleInterval(min + other.min, delta + other.delta);
    r.set_remainder();
    return r;
}

AngleInterval AngleInterval::operator*(AngleInterval &other) const
{
    auto r = AngleInterval(std::min(min * other.min, (min + delta) * (other.min + other.delta)), delta * other.delta);
    r.set_remainder();
    return r;
}

AngleInterval polar::AngleInterval::operator|(AngleInterval &other) const
{
    return AngleInterval::min_max(std::min(min, other.min), std::max(min + delta, other.min + other.delta));
}

bool polar::AngleInterval::operator==(const AngleInterval &other) const
{
    return (min == other.min) && (delta == other.delta);
}

void AngleInterval::set_remainder()
{
    if (min > 2 || min < 0)
    {
        int ratio = min / 2;
        min = min - 2 * ratio;
    }
    if (delta > 2)
    {
        delta = 2;
    }
}

Interval::Interval(PositiveInterval mod, AngleInterval arg) : mod(mod), arg(arg) {}

polar::Interval::Interval() : mod(PositiveInterval(0.)), arg(AngleInterval(0.)) {};

Interval polar::Interval::real(polar::real value)
{
    return Interval::singleton(value);
}

static real argument(const ampl::Amplitude &z)
{
    if (z.imag() == 0)
    {
        return z.real() >= 0 ? 0. : 1.;
    }
    if (z.real() == 1)
    {
        return z.imag() >= 0 ? .5 : 1.5;
    }
    return std::arg(z) / std::numbers::pi;
}

Interval polar::Interval::singleton(ampl::Amplitude z)
{
    auto modulus = std::abs(z);
    auto arg = argument(z);
    if (modulus < 0)
    {
        throw std::range_error("Negative modulus in a polar interval");
    }
    if (arg < 0 || arg > 2)
    {
        throw std::range_error("Bad argument in polar interval: " + std::to_string(arg));
    }
    return Interval(PositiveInterval(modulus), AngleInterval(arg));
}

Interval polar::Interval::exp2iPiOver(int n)
{
    return Interval(PositiveInterval(1.), AngleInterval(2. / n));
}

Interval polar::Interval::operator+(Interval &other) const
{
    if (*this == zero)
    {
        return other;
    }
    if (other == zero)
    {
        return *this;
    }
    if (is_real() && other.is_real())
    {
        return Interval::real(to_real() + other.to_real());
    }
    throw std::logic_error("Sum of polar intervals");
}

Interval Interval::operator*(Interval &other) const
{
    if (*this == zero || other == zero)
    {
        return zero;
    }
    return Interval(mod * other.mod, arg + other.arg);
}

Interval polar::Interval::operator|(Interval &other) const
{
    return Interval(mod | other.mod, arg | other.arg);
}

bool polar::Interval::operator==(const Interval &other) const
{
    return (mod == other.mod) && (arg == other.arg);
}

std::string polar::Interval::to_string(bool strict) const
{
    if (!strict)
    {
        if (is_real())
            return std::to_string(to_real());
    }
    return "{mod: " + std::to_string(mod.min) + " " + std::to_string(mod.max) + " arg: " + std::to_string(arg.min) + " " + std::to_string(arg.delta) + "}";
}

polar::real polar::Interval::norm()
{
    return arg.delta * mod.max; // TODO: better approximation
}

bool polar::Interval::is_real() const
{
    return (arg.delta == 0) && (arg.min == 0. || arg.min == 1.);
}

polar::real polar::Interval::to_real() const
{
    if (!is_real())
    {
        throw std::logic_error("Not a real number");
    }
    return mod.min * ((arg.min == 0.) ? 1. : -1.);
}