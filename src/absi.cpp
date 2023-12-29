#include <absi.h>
#include <algorithm>

using namespace absi;

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
    ampl::real minre, maxre, minim, maxim;
    bool flag = true;
    for (ampl::real rex : reals)
    {
        for (ampl::real imx : imaginaries)
        {
            for (ampl::real rey : other.reals)
            {

                for (ampl::real imy : other.imaginaries)
                {
                    auto rez = rex * rey - imx * imy;
                    auto imz = rex * imy - imx * rey;
                    if (flag || rez < minre)
                    {
                        minre = rez;
                    }
                    if (flag || maxre < rez)
                    {
                        maxre = rez;
                    }
                    if (flag || imz < minim)
                    {
                        minim = imz;
                    }
                    if (flag || maxim < imz)
                    {
                        maxim = imz;
                    }
                    flag = false;
                }
            }
        }
    }
    return AbstractElement(minre, minim, maxre, maxim);
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

ampl::real AbstractElement::includeCost(ampl::Amplitude z) const
{
    if (contains(z))
    {
        return ampl::zero_real;
    }
    ampl::real newReals[2] = {
        std::min(reals[0], z.real()),
        std::max(reals[1], z.real())};
    ampl::real newImaginaries[2] = {
        std::min(imaginaries[0], z.imag()),
        std::max(imaginaries[1], z.imag())};
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