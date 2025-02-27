#pragma once
#include <math.h>
#include <amplitude.h>

namespace polar
{
    using ampl::real;

    class Interval;

    class PositiveInterval
    {
        friend class Interval;

    public:
        PositiveInterval(const real a, const real b);

        PositiveInterval(const real a);

        PositiveInterval operator+(PositiveInterval &other) const;

        PositiveInterval operator*(PositiveInterval &other) const;

        PositiveInterval operator|(PositiveInterval &other) const;

        bool operator==(const PositiveInterval &other) const;

    protected:
        real min;
        real max;
    };

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
        /// Moreover, 0 <= @ref delta <= 2
        real delta;
        void set_remainder();
    };

    class Interval
    {
    public:
        /// @brief The singleton of 0.
        Interval();

        /// @brief The singleton of a real number.
        Interval(const real value);

        /// @brief The singleton of an amplitude.
        Interval(const ampl::Amplitude z);

        Interval(PositiveInterval mod, AngleInterval arg);

        static Interval exp2iPiOver(int n);

        Interval operator+(Interval &other) const;

        Interval operator*(Interval &other) const;

        Interval operator|(Interval &other) const;

        bool operator==(const Interval &other) const;

        std::string to_string(bool strict = false) const;

        polar::real norm();

    protected:
        /**
         * @brief Checks if the number is real.
         *
         * @return true if the number is real, false otherwise.
         */
        bool is_real() const;

        polar::real to_real() const;

        PositiveInterval mod;

        AngleInterval arg;
    };

    const Interval zero = 0.;

    const Interval one = 1.;
}
