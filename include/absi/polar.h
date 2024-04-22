#ifndef POLAR_H
#define POLAR_H 1

#include <math.h>

namespace polar
{
    typedef float real;

    class Interval;

    class PositiveInterval
    {
        friend class Interval;

    public:
        PositiveInterval(real a, real b);

        PositiveInterval(real a);

        PositiveInterval operator+(PositiveInterval &other) const;

        PositiveInterval operator*(PositiveInterval &other) const;

        PositiveInterval operator|(PositiveInterval &other) const;

        bool operator==(const PositiveInterval &other) const;

    protected:
        real min;
        real max;
    };

    constexpr real pi = M_PI;

    class AngleInterval
    {
        friend class Interval;

    public:
        AngleInterval(real min, real delta);

        AngleInterval(real a);

        static AngleInterval min_max(real a, real b);

        AngleInterval operator+(AngleInterval &other) const;

        AngleInterval operator*(AngleInterval &other) const;

        AngleInterval operator|(AngleInterval &other) const;

        bool operator==(const AngleInterval &other) const;

    protected:
        /// @brief The minimal value of the interval
        /// `0 < @ref min < 2` is expressed in radians to limit
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
        /// @brief The singleton of 0.
        Interval();

        Interval(PositiveInterval mod, AngleInterval arg);

        static Interval singleton(real modulus, real argument);

        static Interval real(real value);

        Interval operator+(Interval &other) const;

        Interval operator*(Interval &other) const;

        Interval operator|(Interval &other) const;

        bool operator==(const Interval &other) const;

        std::string to_string() const;

    protected:
        PositiveInterval mod;

        AngleInterval arg;
    };

    inline Interval zero = Interval();

    inline Interval one = Interval::real(1.);
}
#endif