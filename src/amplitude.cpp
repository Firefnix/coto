#include <stdexcept>
#include <amplitude.h>

using namespace ampl;

static int gcd(const int a, const int b)
{
    const int c = abs(a);
    const int d = abs(b);
    return (d == 0) ? c : gcd(d, c % d);
}

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
    int d = gcd(a, b);
    p = a / d;
    q = b / d;
}

Rational Rational::fromInt(const int i)
{
    return {i, 1};
}

bool Rational::operator==(const Rational &other) const
{
    return (p == other.p) && (q == other.q);
}

bool Rational::operator!=(const Rational &other) const
{
    return !(*this == other);
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

Rational Rational::operator/(const Rational &other) const
{
    if (other.p == 0)
    {
        throw std::domain_error(DIVISION_BY_ZERO);
    }
    return Rational(p * other.q, q * other.p);
}

RPR ampl::rpr_int(const int i)
{
    if (i >= 0)
    {
        return RPR(true, Rational::fromInt(i), one_rational);
    }
    return RPR(false, Rational::fromInt(-i), one_rational);
}

Amplitude Amplitude::conj() const
{
    return Amplitude(re, im.opposite());
}

RPR Amplitude::square_module() const
{
    return zero_rpr;
}

Amplitude ampl::ampl_int(const int i)
{
    return Amplitude(rpr_int(i), zero_rpr);
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