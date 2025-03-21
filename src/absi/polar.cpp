#include <absi/polar.h>

#include <stdexcept>
#include <numbers>
#include <iostream>

using namespace polar;

static Real argument(const ampl::Amplitude &z);

PositiveInterval::PositiveInterval(const Real a, const Real b) : min(a), max(b)
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

PositiveInterval::PositiveInterval(const Real a) : min(a), max(a) {}

PositiveInterval PositiveInterval::operator+(const PositiveInterval &other) const
{
    return PositiveInterval(min + other.min, max + other.max);
}

PositiveInterval PositiveInterval::operator*(const PositiveInterval &other) const
{
    return PositiveInterval(min * other.min, max * other.max);
}

PositiveInterval polar::PositiveInterval::operator|(const PositiveInterval &other) const
{
    return PositiveInterval(std::min(min, other.min), std::max(max, other.max));
}

bool polar::PositiveInterval::operator==(const PositiveInterval &other) const
{
    return (min == other.min) && (max == other.max);
}

AngleInterval::AngleInterval(Real min, Real delta) : min(min), delta(delta)
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

AngleInterval::AngleInterval(Real min) : min(min), delta(0.) {}

AngleInterval polar::AngleInterval::min_max(Real a, Real b) noexcept
{
    return AngleInterval(std::min(a, b), std::abs(a - b));
}

AngleInterval AngleInterval::operator+(const AngleInterval &other) const noexcept
{
    auto r = AngleInterval(min + other.min, delta + other.delta);
    r.set_remainder();
    return r;
}

AngleInterval AngleInterval::operator*(const AngleInterval &other) const noexcept
{
    auto r = AngleInterval(std::min(min * other.min, (min + delta) * (other.min + other.delta)), delta * other.delta);
    r.set_remainder();
    return r;
}

AngleInterval polar::AngleInterval::operator|(const AngleInterval &other) const noexcept
{
    return AngleInterval::min_max(std::min(min, other.min), std::max(min + delta, other.min + other.delta));
}

bool polar::AngleInterval::operator==(const AngleInterval &other) const noexcept
{
    return (min == other.min) && (delta == other.delta);
}

void AngleInterval::set_remainder() noexcept
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

polar::Interval::Interval(const polar::Real value) : mod(PositiveInterval(std::abs(value))),
                                               arg(AngleInterval(value < 0. ? 1. : 0.)) {}

polar::Interval::Interval(const ampl::Amplitude z) : mod(PositiveInterval(std::abs(z))), arg(argument(z)) {}

static Real argument(const ampl::Amplitude &z)
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

Interval polar::Interval::exp_2ipi_over(int n)
{
    return Interval(PositiveInterval(1.), AngleInterval(2. / n));
}

Interval polar::Interval::operator+(const Interval &other) const
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
        return Interval(to_real() + other.to_real());
    }
    throw std::logic_error("Sum of polar intervals");
}

Interval Interval::operator*(const Interval &other) const noexcept
{
    if (*this == zero || other == zero)
    {
        return zero;
    }
    return Interval(mod * other.mod, arg + other.arg);
}

Interval polar::Interval::operator|(const Interval &other) const noexcept
{
    return Interval(mod | other.mod, arg | other.arg);
}

bool polar::Interval::operator==(const Interval &other) const noexcept
{
    return (mod == other.mod) && (arg == other.arg);
}

std::string polar::Interval::to_string(bool strict) const noexcept
{
    if (!strict)
    {
        if (is_real())
            return std::to_string(to_real());
    }
    return "{mod: " + std::to_string(mod.min) + " " + std::to_string(mod.max) + " arg: " + std::to_string(arg.min) + " " + std::to_string(arg.delta) + "}";
}

polar::Real polar::Interval::norm()
{
    return arg.delta * mod.max; // TODO: better approximation
}

bool polar::Interval::is_real() const noexcept
{
    return (arg.delta == 0) && (arg.min == 0. || arg.min == 1.);
}

polar::Real polar::Interval::to_real() const
{
    if (!is_real())
    {
        throw std::logic_error("Not a real number");
    }
    return mod.min * ((arg.min == 0.) ? 1. : -1.);
}