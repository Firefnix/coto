#ifndef AMPLITUDE_H_
#define AMPLITUDE_H_ 1

#include <string>
#include <cstddef>

namespace ampl
{
    class RPR;
    class Rational
    {
        friend class RPR;
        friend float realFromRational(const Rational);
        friend float realFromRPR(const RPR rpr);

    public:
        Rational() : p(0), q(1){};
        Rational(const Rational &r) : p(r.p), q(r.q){};
        Rational(const int pp, const int pq);
        static Rational fromInt(const int i);
        Rational operator=(const Rational &tmp) const;
        bool operator==(const Rational &other) const;
        bool operator!=(const Rational &other) const;
        bool operator<(const Rational &other) const;
        bool isNonNegative() const;
        Rational operator+(const Rational &other) const;
        Rational operator*(const Rational &other) const;
        Rational operator*(const int &other) const;
        Rational operator^(const int &other) const;
        Rational operator-() const;
        Rational operator-(const Rational &other) const;
        Rational abs() const;
        Rational inverse() const;
        Rational operator/(const Rational &other) const;

        // private:
        int p, q;
        const std::string DIVISION_BY_ZERO = "Division by zero in Rational";
    };
    const Rational zero_rational = {0, 1};
    const Rational one_rational = {1, 1};

    /** @brief A kind of real number
     *
     * More general than rationals, RPRs are able to store any
     * sigma * (x**q) where sigma is +/-1, and x and q are rationals.
     * Internally, we always take x positive and q = 1 / p with p a positive integer.
     */
    class RPR
    {
    public:
        RPR() : RPR(true, zero_rational, 1){};
        RPR(const RPR &rpr) : sigma(rpr.sigma), x(rpr.x), p(rpr.p){};
        RPR(const bool sigma, const Rational x, const unsigned p);
        static RPR fromInt(const int i);
        static RPR fromRational(const Rational r);
        RPR operator=(const RPR &tmp) const;
        bool operator==(const RPR &other) const;
        bool operator!=(const RPR &other) const;
        bool operator<(const RPR &other) const;
        bool operator<=(const RPR &other) const;
        bool isNonNegative() const;
        RPR operator+(const RPR &other) const;
        RPR operator*(const RPR &other) const;
        RPR operator*(const int &other) const;
        RPR operator-(const RPR &other) const;
        RPR operator-() const;
        RPR abs() const;
        RPR inverse() const;
        RPR operator/(const RPR &other) const;

        // private:
        bool sigma; // true <=> (rpr >= 0)
        Rational x;
        unsigned p;
        bool isRational() const;
        Rational toRational() const;
    };
    const RPR zero_rpr = RPR();
    const RPR one_rpr = RPR(true, {1, 1}, 1);
    const RPR sqrt2_rpr = RPR(true, {2, 1}, 2);

    class FIF
    {
    public:
        FIF(float re, float im) : re(re), im(im){};
        FIF(float re) : re(re), im(0.){};
        FIF operator+(const FIF &other) const;
        FIF operator*(const FIF &other) const;
        FIF operator*(const int &other) const;
        FIF operator-(const FIF &other) const;
        FIF operator-() const;

        float re, im;
    };

    typedef float real;

    real absReal(const real);
    real realFromInt(const int);
    real realFromRational(const Rational);
    real realFromRPR(const RPR);

    const real zero_real = 0.; // zero_rpr;
    const real one_real = 0.;  // one_rpr;
    const real sqrt2_real = sqrt2_real;

    /** @brief A general-purpose complex amplitude
     *
     * Can use either of the x + iy or r*exp(it) representations,
     * in any case it implements the classical complex arithmetic
     * operations. Uses profusiously the `real` type.
     */
    class Amplitude
    {
    public:
        Amplitude() = default;
        Amplitude(const Amplitude &z) : re(z.re), im(z.im){};
        Amplitude(real re, real im) : re(re), im(im){};
        Amplitude(const int i) : re(static_cast<real>(i)), im(zero_real){};
        Amplitude(const int i, const int j) : re(static_cast<real>(i)), im(static_cast<real>(j)){};
        bool operator==(const Amplitude &other) const;
        bool operator!=(const Amplitude &other) const;
        Amplitude operator+(const Amplitude &other) const;
        Amplitude operator*(const Amplitude &other) const;
        Amplitude operator*(const real &other) const;
        Amplitude operator*(const int &other) const;
        Amplitude operator-(const Amplitude &other) const;
        Amplitude operator-() const;

        /// @brief Compute the complex conjugate of an amplitude
        /// @return The complex conjugate of the amplitude
        Amplitude conj() const;

        /// @brief Compute the square module of the amplitude
        /// @return The square module of the amplitude
        real square_module() const;

        real surface() const;
        real re, im;

        /** @brief Generate a random amplitude
         *
         * Generate a complex number (random real and imaginary parts), normalized to have a module
         * m such that m <= 1.
         */
        static Amplitude random();
    };

    const Amplitude zero = Amplitude(zero_real, zero_real);
    const Amplitude one = Amplitude(one_real, zero_real);
    const Amplitude i = Amplitude(zero_real, one_real);
    const Amplitude sqrt2 = Amplitude(sqrt2_real, zero_real);

    std::size_t pow2(std::size_t n);
    std::size_t log2(std::size_t n);
}

#endif