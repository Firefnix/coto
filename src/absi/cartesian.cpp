#include <string>
#include <tuple>

#include <absi/cartesian.h>

using namespace cartesian;

/// @brief Minimum and maximum of xy for x in [xn, xx] and y in [yn, yx]
static cartesian::RealInterval min_max_of_product(const RealInterval x, const RealInterval y);

Interval::Interval() : bottom_left{0.}, top_right{0.} {};

Interval::Interval(RealInterval re, RealInterval im) : bottom_left{std::min(std::get<0>(re), std::get<1>(re)), std::min(std::get<0>(im), std::get<1>(im))},
                                                       top_right{std::max(std::get<0>(re), std::get<1>(re)), std::max(std::get<0>(im), std::get<1>(im))} {};

Interval::Interval(const ampl::Real value) : bottom_left{value}, top_right{value} {};

Interval::Interval(const ampl::Amplitude z) : bottom_left{z}, top_right{z} {};

bool Interval::operator==(const Interval &other) const
{
    return (bottom_left == other.bottom_left) && (top_right == other.top_right);
}

Interval Interval::operator-() const
{
    return Interval(ampl::Amplitude(-top_right.real(), -top_right.imag()),
                    ampl::Amplitude(-bottom_left.real(), -bottom_left.imag()));
}

Interval Interval::operator|(const Interval &other) const
{
    return {ampl::Amplitude(std::min(bottom_left.real(), other.bottom_left.real()), std::min(bottom_left.imag(), other.bottom_left.imag())),
            ampl::Amplitude(std::max(top_right.real(), other.top_right.real()), std::max(top_right.imag(), other.top_right.imag()))};
}

Interval Interval::operator+(const Interval &other) const
{
    return {ampl::Amplitude(bottom_left.real() + other.bottom_left.real(), bottom_left.imag() + other.bottom_left.imag()),
            ampl::Amplitude(top_right.real() + other.top_right.real(), top_right.imag() + other.top_right.imag())};
}

Interval Interval::operator*(const ampl::Real &other) const
{
    if (other >= ampl::zero_real)
    {
        return Interval(bottom_left * other, top_right * other);
    }
    return -(*this * (-other));
}

Interval Interval::operator*(const Interval &other) const
{
    return Interval(
        min_max_of_product(reals(), other.reals()),
        min_max_of_product(imaginaries(), other.imaginaries()));
}

ampl::Real Interval::operator^(const Interval &other) const
{
    ampl::Real total = (*this | other).norm();
    return (total * 2) - norm() - other.norm();
}

bool Interval::contains(ampl::Amplitude z) const
{
    return (bottom_left.real() <= z.real()) &&
           (z.real() <= top_right.real()) &&
           (bottom_left.imag() <= z.imag()) &&
           (z.imag() <= top_right.imag());
}

ampl::Real Interval::norm() const noexcept
{
    return abs(top_right - bottom_left);
}

std::string Interval::to_string() const noexcept
{
    return "[" + ampl::to_string(bottom_left) + ", " + ampl::to_string(top_right) + "]";
}

static RealInterval min_max_of_product(const RealInterval x, const RealInterval y)
{
    ampl::Real x1 = std::get<0>(x), x2 = std::get<1>(x), y1 = std::get<0>(y), y2 = std::get<1>(y);
    ampl::Real values[4] = {x1 * y1, x1 * y2, x2 * y1, x2 * y2};
    ampl::Real rmin = values[0], rmax = values[0];
    for (int i = 1; i < 4; i++)
    {
        if (values[i] < rmin)
        {
            rmin = values[i];
        }
        else if (values[i] > rmax)
        {
            rmax = values[i];
        }
    }
    return std::make_tuple(rmin, rmax);
}

RealInterval Interval::reals() const noexcept
{
    return std::make_tuple(bottom_left.real(), top_right.real());
}

RealInterval Interval::imaginaries() const noexcept
{
    return std::make_tuple(bottom_left.imag(), top_right.imag());
}
