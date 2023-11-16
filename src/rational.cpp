#include <calc.h>

/**
 * TYPING methods (type, toInteger, toRational)
 */

NT Rational::type() const
{
    return NT::Rational;
}

Integer Rational::toInteger() const
{
    if (p % q == 0)
    {
        return Integer(p / q);
    }
    throw std::invalid_argument("Rational cannot have zero denominator");
}

Rational Rational::toRational() const
{
    return *this;
}

/**
 * OPERATING methods (gcd, isZero, simple)
 */

int Rational::gcd(const int a, const int b)
{
    const int c = Integer::absolute(a);
    const int d = Integer::absolute(b);
    return (d == 0) ? c : Rational::gcd(d, c % d);
}

bool Rational::isZero() const
{
    return p == 0;
}

Number Rational::simple() const
{
    if (p % q == 0)
    {
        return Integer(p / q);
    }
    return *this;
}

/**
 * TESTING methods ()
 */
