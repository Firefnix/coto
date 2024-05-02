#include <algorithm>
#include <tuple>

#include <absi/cartesian.h>

using namespace cartesian;

// @brief Minimum and maximum of xy for x in [xn, xx] and y in [yn, yx]
static cartesian::real_interval minMaxOfProduct(real_interval x, real_interval y);

Interval Interval::operator-() const
{
    return Interval(ampl::Amplitude(-topRight.real(), -topRight.imag()),
                    ampl::Amplitude(-bottomLeft.real(), -bottomLeft.imag()));
}

Interval Interval::operator||(const Interval &other) const
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
    // TODO: not implemented yet (the formulas exist on paper)
    return *this;
}

ampl::real Interval::operator^(const Interval &other) const
{
    ampl::real total = (*this || other).norm();
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

static real_interval minMaxOfProduct(real_interval x, real_interval y)
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
