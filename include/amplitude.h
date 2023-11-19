#ifndef AMPLITUDE_H_
#define AMPLITUDE_H_ 1

#include <string>
#include <cstddef>

namespace ampl
{
    class Rational
    {
    public:
        Rational() : p(0), q(1){};
        Rational(const Rational &r) : p(r.p), q(r.q){};
        Rational(const int p, const int q);
        static Rational fromInt(const int i);
        bool operator==(const Rational &other) const;
        bool operator!=(const Rational &other) const;
        Rational operator+(const Rational &other) const;
        Rational operator*(const Rational &other) const;
        Rational operator-() const;
        Rational operator-(const Rational &other) const;
        Rational operator/(const Rational &other) const;

    private:
        int p, q;
        const std::string DIVISION_BY_ZERO = "Division by zero in Rational";
    };
    const Rational zero_rational = {0, 1};
    const Rational one_rational = {1, 1};

    class RPR
    {
    public:
        RPR() : RPR(true, zero_rational, one_rational){};
        RPR(bool sigma, Rational base, Rational power) : sigma(sigma), base(base), power(power){};
        RPR opposite() const
        {
            return RPR(not sigma, base, power);
        }
        auto operator==(const RPR &other) const
        {
            return (sigma == other.sigma) && (base == other.base) && (power == other.power);
        }
        auto operator!=(const RPR &other) const { return !(*this == other); }

    private:
        bool sigma; // true <=> (rpr >= 0)
        Rational base, power;
    };
    RPR rpr_int(const int i);
    const RPR zero_rpr = RPR();
    const RPR one_rpr = RPR(true, one_rational, one_rational);

    class Amplitude
    {
    public:
        Amplitude(RPR re, RPR im) : re(re), im(im){};
        Amplitude conj() const;
        RPR square_module() const;
        auto operator==(const Amplitude &other) const
        {
            return (re == other.re) && (im == other.im);
        }
        auto operator!=(const Amplitude &other) const { return !(*this == other); }

    private:
        RPR re, im;
    };

    Amplitude ampl_int(const int i);
    const Amplitude zero = Amplitude(zero_rpr, zero_rpr);
    const Amplitude one = Amplitude(one_rpr, zero_rpr);

    std::size_t pow2(std::size_t n);
    std::size_t log2(std::size_t n);
}

#endif