/**
 * ABStract Interpretation (AbsI)
 */

#ifndef ABSI_H_
#define ABSI_H_ 1

#include <amplitude.h>
#include <tuple>

namespace cartesian
{
    typedef std::tuple<ampl::real, ampl::real> real_interval;

    class Interval
    {
    public:
        Interval(ampl::Amplitude z)
            : bottomLeft(z),
              topRight(z),
              reals{z.real(), z.real()},
              imaginaries{z.imag(), z.imag()} {};
        Interval(ampl::Amplitude u, ampl::Amplitude v)
            : bottomLeft(u),
              topRight(v),
              reals{u.real(), v.real()},
              imaginaries{u.imag(), v.imag()} {};
        Interval(ampl::real a, ampl::real b, ampl::real c, ampl::real d)
            : bottomLeft(ampl::Amplitude(a, b)),
              topRight(ampl::Amplitude(c, d)),
              reals{a, c},
              imaginaries{b, d} {};
        Interval operator-() const;
        Interval operator||(const Interval &other) const; // union
        Interval operator+(const Interval &other) const;
        Interval operator*(const ampl::real &other) const;
        Interval operator*(const Interval &other) const;
        ampl::real operator^(const Interval &other) const; // distance
        bool contains(ampl::Amplitude) const;
        ampl::real norm() const;

    protected:
        ampl::Amplitude bottomLeft, topRight;
        real_interval reals;
        real_interval imaginaries;
    };

    inline cartesian::Interval zero = Interval(ampl::zero);
}

#endif