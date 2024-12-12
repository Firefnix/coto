#include <string>
#include <tuple>

#include <absi/cartesian.h>

using namespace cartesian;

/// @brief Minimum and maximum of xy for x in [xn, xx] and y in [yn, yx]
static cartesian::real_interval minMaxOfProduct(const real_interval x, const real_interval y);

Interval::Interval() : bottomLeft{0.}, topRight{0.} {};

Interval::Interval(real_interval re, real_interval im) :
    bottomLeft{std::min(std::get<0>(re), std::get<1>(re)), std::min(std::get<0>(im), std::get<1>(im))},
    topRight{std::max(std::get<0>(re), std::get<1>(re)), std::max(std::get<0>(im), std::get<1>(im))} {};

Interval Interval::real(const ampl::real value)
{
    return Interval::singleton(value);
}

Interval Interval::singleton(ampl::Amplitude z)
{
    return Interval(z, z);
}

bool Interval::operator==(const Interval &other) const
{
    return (bottomLeft == other.bottomLeft) && (topRight == other.topRight);
}


Interval Interval::operator-() const
{
    return Interval(ampl::Amplitude(-topRight.real(), -topRight.imag()),
                    ampl::Amplitude(-bottomLeft.real(), -bottomLeft.imag()));
}

Interval Interval::operator|(const Interval &other) const
{
    return {ampl::Amplitude(std::min(bottomLeft.real(), other.bottomLeft.real()), std::min(bottomLeft.imag(), other.bottomLeft.imag())),
            ampl::Amplitude(std::max(topRight.real(), other.topRight.real()), std::max(topRight.imag(), other.topRight.imag()))};
}

Interval Interval::operator+(const Interval &other) const
{
    return {ampl::Amplitude(bottomLeft.real() + other.bottomLeft.real(), bottomLeft.imag() + other.bottomLeft.imag()),
            ampl::Amplitude(topRight.real() + other.topRight.real(), topRight.imag() + other.topRight.imag())};
}

Interval Interval::operator*(const ampl::real &other) const
{
    if (other >= ampl::zero_real)
    {
        return Interval(bottomLeft * other, topRight * other);
    }
    return -(*this * (-other));
}

Interval Interval::operator*(const Interval &other) const
{
    return Interval(
        minMaxOfProduct(reals(), other.reals()),
        minMaxOfProduct(imaginaries(), other.imaginaries())
    );
}

ampl::real Interval::operator^(const Interval &other) const
{
    ampl::real total = (*this | other).norm();
    return (total * 2) - norm() - other.norm();
}

bool Interval::contains(ampl::Amplitude z) const
{
    return (bottomLeft.real() <= z.real()) &&
           (z.real() <= topRight.real()) &&
           (bottomLeft.imag() <= z.imag()) &&
           (z.imag() <= topRight.imag());
}

ampl::real Interval::norm() const
{
    return abs(topRight - bottomLeft);
}

std::string Interval::to_string() const
{
    return "[" + ampl::to_string(bottomLeft) + ", " + ampl::to_string(topRight) + "]";
}

static real_interval minMaxOfProduct(const real_interval x, const real_interval y)
{
    ampl::real x1 = std::get<0>(x), x2 = std::get<1>(x), y1 = std::get<0>(y), y2 = std::get<1>(y);
    ampl::real values[4] = {x1 * y1, x1 * y2, x2 * y1, x2 * y2};
    ampl::real rmin = values[0], rmax = values[0];
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

real_interval Interval::reals() const
{
    return std::make_tuple(bottomLeft.real(), topRight.real());
}

real_interval Interval::imaginaries() const
{
    return std::make_tuple(bottomLeft.imag(), topRight.imag());
}
