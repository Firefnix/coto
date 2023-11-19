#ifndef AMPLITUDE_H_
#define AMPLITUDE_H_ 1

namespace ampl
{
    struct rational
    {
        int p;
        int q;
        auto operator==(const rational &other) const
        {
            return (p == other.p) && (q == other.q);
        };
        auto operator!=(const rational &other) const { return !(*this == other); }
    };
    rational rat_int(const int i);
    const rational zero_rational = {0, 1};

    class RPR
    {
    public:
        RPR() : RPR(true, zero_rational, {1, 1}){};
        RPR(bool sigma, rational base, rational power) : sigma(sigma), base(base), power(power){};
        RPR(const RPR &rpr)
        {
            sigma = rpr.sigma;
            base = rpr.base;
            power = rpr.power;
        }
        RPR opposite() const
        {
            return RPR(not sigma, base, power);
        }
        auto operator==(const RPR &other) const
        {
            return (sigma == other.sigma) && (base == other.base) && (power == other.power);
        }
        auto operator!=(const RPR &other) const { return !(*this == other); }

        // private:
        bool sigma; // true <=> (rpr >= 0)
        rational base, power;
    };
    RPR rpr_int(const int i);
    const RPR zero_rpr = RPR();

    class Amplitude
    {
    public:
        Amplitude(const Amplitude &a)
        {
            re = a.re;
            im = a.im;
        }
        Amplitude(RPR re, RPR im) : re(re), im(im){};
        Amplitude conj() const;
        RPR square_module() const;
        auto operator==(const Amplitude &other) const
        {
            return (re == other.re) && (im == other.im);
        }
        auto operator!=(const Amplitude &other) const { return !(*this == other); }

        // private:
        RPR re, im;
    };

    Amplitude ampl_int(const int i);
    const Amplitude zero = Amplitude(zero_rpr, zero_rpr);
}

#endif