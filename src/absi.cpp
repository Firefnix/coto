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

real_interval absi::AbstractElement::real_interval()
{
    return real_interval();
}

ampl::real AbstractElement::includeCost(ampl::Amplitude z) const
{
    if (contains(z))
    {
        return ampl::zero_real;
    }
    ampl::real a = std::get<0>(reals);
    ampl::real newReals[2] = {
        std::min(std::get<0>(reals), z.real()),
        std::max(std::get<1>(reals), z.real())};
    ampl::real newImaginaries[2] = {
        std::min(std::get<0>(imaginaries), z.imag()),
        std::max(std::get<1>(imaginaries), z.imag())};
    ampl::real newSurface = (newReals[1] - newReals[0]) * (newImaginaries[1] - newImaginaries[0]);
    return newSurface - norm();
}

void AbstractElement::include(ampl::Amplitude z)
{
    reals[0] = std::min(reals[0], z.real());
    reals[1] = std::max(reals[1], z.real());
    imaginaries[0] = std::min(imaginaries[0], z.imag());
    imaginaries[1] = std::max(imaginaries[1], z.imag());
    bottomLeft = ampl::Amplitude(reals[0], imaginaries[0]);
    topRight = ampl::Amplitude(reals[1], imaginaries[1]);
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
