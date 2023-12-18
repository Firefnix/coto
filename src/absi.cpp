#include <absi.h>
#include <algorithm>

using namespace absi;

AbstractElement AbstractElement::operator-() const
{
    return AbstractElement(ampl::Amplitude(-topRight.re, -topRight.im),
                           ampl::Amplitude(-bottomLeft.re, -bottomLeft.im));
}

AbstractElement AbstractElement::operator||(const AbstractElement &other) const
{
    return {ampl::Amplitude(std::min(bottomLeft.re, other.bottomLeft.re), std::min(bottomLeft.im, other.bottomLeft.im)),
            ampl::Amplitude(std::max(topRight.re, other.topRight.re), std::max(topRight.im, other.topRight.im))};
}

AbstractElement AbstractElement::operator+(const AbstractElement &other) const
{
    return {ampl::Amplitude(bottomLeft.re + other.bottomLeft.re, bottomLeft.im + other.bottomLeft.im),
            ampl::Amplitude(topRight.re + other.topRight.re, topRight.im + other.topRight.im)};
}

AbstractElement AbstractElement::operator*(const ampl::real &other) const
{
    if (other.isNonNegative())
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
    ampl::real total = (*this || other).surface();
    return (total * 2) - surface() - other.surface();
}

bool AbstractElement::contains(ampl::Amplitude z) const
{
    return (bottomLeft.re <= z.re) &&
           (z.re <= topRight.re) &&
           (bottomLeft.im <= z.im) &&
           (z.im <= topRight.im);
}

ampl::real AbstractElement::surface() const
{
    return (topRight - bottomLeft).surface();
}

ampl::real AbstractElement::includeCost(ampl::Amplitude z) const
{
    if (contains(z))
    {
        return ampl::zero_real;
    }
    ampl::real newReals[2] = {
        std::min(reals[0], z.re),
        std::max(reals[1], z.re)};
    ampl::real newImaginaries[2] = {
        std::min(imaginaries[0], z.im),
        std::max(imaginaries[1], z.im)};
    ampl::real newSurface = (newReals[1] - newReals[0]) * (newImaginaries[1] - newImaginaries[0]);
    return newSurface - surface();
}

void AbstractElement::include(ampl::Amplitude z)
{
    reals[0] = std::min(reals[0], z.re);
    reals[1] = std::max(reals[1], z.re);
    imaginaries[0] = std::min(imaginaries[0], z.im);
    imaginaries[1] = std::max(imaginaries[1], z.im);
    bottomLeft = ampl::Amplitude(reals[0], imaginaries[0]);
    topRight = ampl::Amplitude(reals[1], imaginaries[1]);
}