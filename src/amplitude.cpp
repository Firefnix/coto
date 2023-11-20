#include <stdexcept>
#include <amplitude.h>
#include <cmath>
#include <numeric>

using namespace ampl;

Rational::Rational(const int pp, const int pq)
{
    int a = pp, b = pq;
    if (b == 0)
    {
        throw std::domain_error(DIVISION_BY_ZERO);
    }
    if (b < 0)
    {
        a = -a;
        b = -b;
    }
    int d = std::gcd(a, b);
    p = a / d;
    q = b / d;
}

Rational Rational::fromInt(const int i)
{
    return {i, 1};
}

Rational Rational::operator=(const Rational &tmp) const
{
    std::swap(*this, tmp);
    return *this;
}

bool Rational::operator==(const Rational &other) const
{
    return (p == other.p) && (q == other.q);
}

bool Rational::operator!=(const Rational &other) const
{
    return !(*this == other);
}

bool Rational::isNonNegative() const
{
    return p >= 0;
}

Rational Rational::operator+(const Rational &other) const
{
    return Rational(p * other.q + other.p * q, q * other.q);
}

Rational Rational::operator*(const Rational &other) const
{
    return Rational(p * other.p, q * other.q);
}

Rational Rational::operator-() const
{
    return Rational(-p, q);
}

Rational Rational::operator-(const Rational &other) const
{
    return Rational(p * other.q - other.p * q, q * other.q);
}

Rational Rational::abs() const
{
    return Rational(std::abs(p), q);
}

Rational Rational::inverse() const
{
    return Rational(q, p);
}

Rational Rational::operator/(const Rational &other) const
{
    if (other.p == 0)
    {
        throw std::domain_error(DIVISION_BY_ZERO);
    }
    return Rational(p * other.q, q * other.p);
}

RPR::RPR(const bool s, const Rational base, const unsigned pp)
{
    if (not base.isNonNegative())
    {
        throw std::domain_error("Negative RPR base");
    }
    sigma = s;
    // x = base;
    p = pp;
}

RPR::RPR(const bool s, const Rational base, const Rational power)
{
    if (not base.isNonNegative())
    {
        throw std::domain_error("Negative RPR base");
    }
    sigma = s;
    auto mp = power;
    if (not power.isNonNegative())
    {
        x = base.inverse();
        mp = -power;
    }
    Rational x(std::pow(base.p, mp.p), std::pow(base.q, mp.p));
    p = mp.q;
}

RPR ampl::RPR::fromInt(const int i)
{
    if (i >= 0)
    {
        return RPR(true, Rational::fromInt(i), 1);
    }
    return RPR(false, Rational::fromInt(-i), 1);
}

RPR ampl::RPR::fromRational(const Rational r)
{

    return RPR();
}

RPR RPR::operator=(const RPR &tmp) const
{
    std::swap(*this, tmp);
    return *this;
}

bool RPR::operator==(const RPR &other) const
{
    return (sigma == other.sigma) && (x == other.x) && (p == other.p);
}

bool RPR::operator!=(const RPR &other) const { return !(*this == other); }

bool RPR::isNonNegative() const { return sigma; }

RPR RPR::operator+(const RPR &other) const
{
    if (*this == -other)
    {
        return zero_rpr;
    }
    if (*this == zero_rpr)
    {
        return other;
    }
    if (other == zero_rpr)
    {
        return *this;
    }
    auto a = other / *this; // can throw a std::domain_error
    if (a.isRational())
    {
        return (one_rpr + a) * (*this);
    }
    throw std::logic_error("Should be unreachable");
}

RPR RPR::operator*(const RPR &other) const
{
    bool s = (sigma == other.sigma); // sign of the product
    if (x == other.x)
    {
        return RPR(s, x, power + other.power);
    }
    if (x == other.x.inverse())
    {
        return RPR(s, x, power + other.power);
    }
    if (power == other.power)
    {
        return RPR(s, x * other.x, power);
    }
    if (power == other.power)
    {
        return RPR(s, x * other.x, power);
    }
    throw std::domain_error("RPRs unable to be multiplied");
}

RPR RPR::operator-(const RPR &other) const
{
    return (*this) + (-other);
}

RPR RPR::operator-() const
{
    return RPR(not sigma, x, p);
}

RPR RPR::inverse() const
{
    return RPR(sigma, x.inverse(), p);
}

RPR RPR::operator/(const RPR &other) const
{
    return *this * other.inverse();
}

bool RPR::isRational() const
{
    return p == 1;
}

Amplitude ampl::Amplitude::fromInt(const int i)
{
    return Amplitude(RPR::fromInt(i), zero_rpr);
}

Amplitude ampl::Amplitude::fromInts(const int i, const int j)
{
    return Amplitude(RPR::fromInt(i), RPR::fromInt(j));
}

bool Amplitude::operator==(const Amplitude &other) const
{
    return (re == other.re) && (im == other.im);
}

bool Amplitude::operator!=(const Amplitude &other) const { return !(*this == other); }

Amplitude Amplitude::operator+(const Amplitude &other) const
{
    return Amplitude(re + other.re, im + other.im);
}

Amplitude Amplitude::operator*(const Amplitude &other) const
{
    return Amplitude(re * other.re - im * other.im, re * other.im + im * other.re);
}

Amplitude Amplitude::operator-(const Amplitude &other) const
{
    return Amplitude(re - other.re, im - other.im);
}

Amplitude Amplitude::operator-() const
{
    return Amplitude(-re, -im);
}

Amplitude Amplitude::conj() const
{
    return Amplitude(re, -im);
}

RPR Amplitude::square_module() const
{
    return zero_rpr;
}

Amplitude ampl::ampl_int(const int i)
{
    return Amplitude(RPR::fromInt(i), zero_rpr);
}

std::size_t ampl::pow2(std::size_t n)
{
    switch (n)
    {
    case 0:
        return 1;
    case 1:
        return 2;
    default:
        std::size_t a = ampl::pow2(n / 2);
        if (n % 2 == 0)
        {
            return a * a;
        }
        return 2 * a * a;
    }
}

std::size_t ampl::log2(std::size_t n)
{
    if (n < 2)
    {
        return 0;
    }
    return 1 + ampl::log2(n / 2);
}
