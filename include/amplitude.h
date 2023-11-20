#ifndef AMPLITUDE_H_
#define AMPLITUDE_H_ 1

#include <string>
#include <cstddef>

namespace ampl
{
    // class RPR;
    class Rational
    {
        friend class RPR;

    public:
        Rational() : p(0), q(1){};
        Rational(const Rational &r) : p(r.p), q(r.q){};
        Rational(const int p, const int q);
        static Rational fromInt(const int i);
        Rational operator=(const Rational &tmp) const;
        bool operator==(const Rational &other) const;
        bool operator!=(const Rational &other) const;
        bool isNonNegative() const;
        Rational operator+(const Rational &other) const;
        Rational operator*(const Rational &other) const;
        Rational operator-() const;
        Rational operator-(const Rational &other) const;
        Rational abs() const;
        Rational inverse() const;
        Rational operator/(const Rational &other) const;

    private:
        int p, q;
        const std::string DIVISION_BY_ZERO = "Division by zero in Rational";
    };
    const Rational zero_rational = {0, 1};
    const Rational one_rational = {1, 1};

    /** @brief A kind a real number
     *
     * More general than rationals, RPRs are able to store any
     * sigma * (x**q) where sigma is +/-1, and x and q are rationals.
     * Internally, we always take x positive and q = 1 / p with p a positive integer.
     */
    class RPR
    {
    public:
        RPR() : RPR(true, zero_rational, one_rational){};
        RPR(const RPR &rpr) : sigma(rpr.sigma), x(rpr.x), p(rpr.p), power(rpr.power){};
        RPR(const bool sigma, const Rational base, const unsigned p);
        RPR(const bool sigma, const Rational base, const Rational power);
        static RPR fromInt(const int i);
        static RPR fromRational(const Rational r);
        RPR operator=(const RPR &tmp) const;
        bool operator==(const RPR &other) const;
        bool operator!=(const RPR &other) const;
        bool isNonNegative() const;
        RPR operator+(const RPR &other) const;
        RPR operator*(const RPR &other) const;
        RPR operator-(const RPR &other) const;
        RPR operator-() const;
        RPR inverse() const;
        RPR operator/(const RPR &other) const;

    private:
        bool sigma; // true <=> (rpr >= 0)
        Rational x;
        unsigned p;
        bool isRational() const;
        Rational power;
    };
    const RPR zero_rpr = RPR();
    const RPR one_rpr = RPR(true, one_rational, 1);
    const RPR sqrt2_rpr = RPR(true, {2, 1}, 2);

    class Amplitude
    {
    public:
        Amplitude(RPR re, RPR im) : re(re), im(im){};
        static Amplitude fromInt(const int i);
        static Amplitude fromInts(const int i, const int j);
        bool operator==(const Amplitude &other) const;
        bool operator!=(const Amplitude &other) const;
        Amplitude operator+(const Amplitude &other) const;
        Amplitude operator*(const Amplitude &other) const;
        Amplitude operator-(const Amplitude &other) const;
        Amplitude operator-() const;
        Amplitude conj() const;
        RPR square_module() const;

    private:
        RPR re, im;
    };

    Amplitude ampl_int(const int i);
    const Amplitude zero = Amplitude(zero_rpr, zero_rpr);
    const Amplitude one = Amplitude(one_rpr, zero_rpr);
    const Amplitude i = Amplitude(zero_rpr, one_rpr);
    const Amplitude sqrt2 = Amplitude(sqrt2_rpr, zero_rpr);

    std::size_t pow2(std::size_t n);
    std::size_t log2(std::size_t n);
}

#endif