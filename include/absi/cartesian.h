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

    /// @brief Represents an interval in the Cartesian coordinate system.
    class Interval {
    public:
        /// @brief A single point interval.
        /// @param z The complex point.
        Interval(ampl::Amplitude z)
            : bottomLeft(z),
              topRight(z),
              reals{z.real(), z.real()},
              imaginaries{z.imag(), z.imag()} {};

        /// @brief The interval between two complex points.
        /// @param u The first complex point.
        /// @param v The second complex point.
        Interval(ampl::Amplitude u, ampl::Amplitude v)
            : bottomLeft(u),
              topRight(v),
              reals{u.real(), v.real()},
              imaginaries{u.imag(), v.imag()} {};

        /// @brief The interval between four real numbers.
        /// @param a The first real part number.
        /// @param b The second real part number.
        /// @param c The first imaginary part number.
        /// @param d The second imaginary part number.
        Interval(ampl::real a, ampl::real b, ampl::real c, ampl::real d)
            : bottomLeft(ampl::Amplitude(a, b)),
              topRight(ampl::Amplitude(c, d)),
              reals{a, c},
              imaginaries{b, d} {};

        /// @brief Negates the interval.
        /// @return The negated interval.
        Interval operator-() const;

        /// @brief Computes the union of two intervals.
        /// @param other The other interval.
        /// @return The union of the two intervals.
        Interval operator||(const Interval &other) const;

        /// @brief Computes the sum of two intervals.
        /// @param other The other interval.
        /// @return The sum of the two intervals.
        Interval operator+(const Interval &other) const;

        /// @brief Computes the product of an interval and a real number.
        /// @param other The real number.
        /// @return The product of the interval and the real number.
        Interval operator*(const ampl::real &other) const;

        /// @brief Computes the product of two intervals.
        /// @param other The other interval.
        /// @return The product of the two intervals.
        Interval operator*(const Interval &other) const;

        /// @brief Computes the distance between two intervals.
        /// @param other The other interval.
        /// @return The distance between the two intervals.
        ampl::real operator^(const Interval &other) const;

        /// @brief Checks if a complex point is contained within the interval.
        /// @param point The complex point.
        /// @return True if the point is contained within the interval, false otherwise.
        bool contains(ampl::Amplitude point) const;

        /// @brief Computes the norm of the interval.
        /// @return The norm of the interval.
        ampl::real norm() const;

    protected:
        ampl::Amplitude bottomLeft; ///< The bottom-left complex point of the interval.
        ampl::Amplitude topRight; ///< The top-right complex point of the interval.
        real_interval reals; ///< The interval of real numbers.
        real_interval imaginaries; ///< The interval of imaginary numbers.
    };

    inline cartesian::Interval zero = Interval(ampl::zero);
}

#endif