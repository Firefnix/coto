#ifndef POLAR_H
#define POLAR_H 1

#include <math.h>

namespace polar
{
    typedef float real;

    class PositiveInterval
    {
    public:
        PositiveInterval(real a, real b);

        PositiveInterval(real a);

        PositiveInterval operator+(PositiveInterval other);

        PositiveInterval operator*(PositiveInterval other);

        PositiveInterval operator|(PositiveInterval other);

    protected:
        real min;
        real max;
    };

    constexpr real pi = M_PI;

    class AngleInterval
    {
    public:
        AngleInterval(real min, real delta);

        AngleInterval(real a);

        static AngleInterval min_max(real a, real b);

        AngleInterval operator+(AngleInterval other);

        AngleInterval operator*(AngleInterval other);

        AngleInterval operator|(AngleInterval other);

    protected:
        /// @brief The minimal value of the interval
        /// 0 < @ref min < 2 is expressed in radians to limit
        real min;

        /// @brief The wideness/uncertainty of the interval
        /// Values in the interval are between @ref min and @ref min + @ref delta
        /// Moreover, 0 < @ref delta <= 2*pi
        real delta;
        void set_remainder();
    };

    class Interval
    {
    public:
        Interval(PositiveInterval mod, AngleInterval arg);

        static Interval singleton(real modulus, real argument);

        Interval operator*(Interval other);

        Interval operator|(Interval other);

    protected:
        PositiveInterval mod;

        AngleInterval arg;
    };
}
#endif