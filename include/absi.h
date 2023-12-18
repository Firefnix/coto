/**
 * ABStract Interpretation (AbsI)
 */

#ifndef ABSI_H_
#define ABSI_H_ 1

#include <amplitude.h>

namespace absi
{
    class AbstractElement
    {
    public:
        AbstractElement(ampl::Amplitude z)
            : bottomLeft(z),
              topRight(z),
              reals({z.re, z.re}),
              imaginaries({z.im, z.im}){};
        AbstractElement(ampl::Amplitude u, ampl::Amplitude v)
            : bottomLeft(u),
              topRight(v),
              reals({u.re, v.re}),
              imaginaries({u.im, v.im}){};
        AbstractElement(ampl::real a, ampl::real b, ampl::real c, ampl::real d)
            : bottomLeft(ampl::Amplitude(a, b)),
              topRight(ampl::Amplitude(c, d)),
              reals({a, c}),
              imaginaries({b, d}){};
        AbstractElement operator-() const;
        AbstractElement operator||(const AbstractElement &other) const; // union
        AbstractElement operator+(const AbstractElement &other) const;
        AbstractElement operator*(const ampl::real &other) const;
        AbstractElement operator*(const AbstractElement &other) const;
        ampl::real operator^(const AbstractElement &other) const; // distance
        bool contains(ampl::Amplitude) const;
        ampl::real includeCost(ampl::Amplitude) const;
        void include(ampl::Amplitude);
        ampl::real surface() const;

    protected:
        ampl::Amplitude bottomLeft, topRight;
        ampl::real reals[2];
        ampl::real imaginaries[2];
    };
}

#endif