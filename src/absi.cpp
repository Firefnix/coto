#include <absi.h>
#include <algorithm>
#include <tuple>

using namespace absi;


// @brief Minimum and maximum of xy for x in [xn, xx] and y in [yn, yx]
static absi::real_interval minMaxOfProduct(real_interval x, real_interval y);

AbstractElement AbstractElement::operator-() const
{
    return AbstractElement(ampl::Amplitude(-topRight.real(), -topRight.imag()),
                           ampl::Amplitude(-bottomLeft.real(), -bottomLeft.imag()));
}

AbstractElement AbstractElement::operator||(const AbstractElement &other) const
{
    return {ampl::Amplitude(std::min(bottomLeft.real(), other.bottomLeft.real()), std::min(bottomLeft.imag(), other.bottomLeft.imag())),
            ampl::Amplitude(std::max(topRight.real(), other.topRight.real()), std::max(topRight.imag(), other.topRight.imag()))};
}

AbstractElement AbstractElement::operator+(const AbstractElement &other) const
{
    return {ampl::Amplitude(bottomLeft.real() + other.bottomLeft.real(), bottomLeft.imag() + other.bottomLeft.imag()),
            ampl::Amplitude(topRight.real() + other.topRight.real(), topRight.imag() + other.topRight.imag())};
}

AbstractElement AbstractElement::operator*(const ampl::real &other) const
{
    if (other >= ampl::zero_real)
    {
        return AbstractElement(bottomLeft * other, topRight * other);
    }
    return -(*this * (-other));
}

AbstractElement AbstractElement::operator*(const AbstractElement &other) const
{
    // TODO: not implemented yet (the formulas exist on paper)
    return *this;
}

ampl::real AbstractElement::operator^(const AbstractElement &other) const
{
    ampl::real total = (*this || other).norm();
    return (total * 2) - norm() - other.norm();
}

bool AbstractElement::contains(ampl::Amplitude z) const
{
    return (bottomLeft.real() <= z.real()) &&
           (z.real() <= topRight.real()) &&
           (bottomLeft.imag() <= z.imag()) &&
           (z.imag() <= topRight.imag());
}

ampl::real AbstractElement::norm() const
{
    return abs(topRight - bottomLeft);
}

static real_interval minMaxOfProduct(real_interval x, real_interval y)
{
    ampl::real x1 = std::get<0>(x), x2 = std::get<1>(x), y1 = std::get<0>(y), y2 = std::get<1>(y);
    ampl::real values[4] = {x1 * y1, x1 * y2, x2 * y1, x2 * y2};
    ampl::real rmin = values[0], rmax = values[0];
    for (uint8_t i = 1; i < 4; i++)
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
