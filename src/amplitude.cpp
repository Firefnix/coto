#include <stdexcept>
#include <amplitude.h>
#include <cmath>
#include <numeric>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace ampl;

Rational::Rational(const int pp, const int pq)
{
    int a = pp, b = pq;
    if (b == 0)
    {
        throw std::domain_error(DIVISION_BY_ZERO + " (constructor)");
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

bool Rational::operator<(const Rational &other) const
{
    return (p * other.q) < (other.p * q);
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

Rational Rational::operator*(const int &other) const
{
    return Rational(p * other, q);
}

Rational Rational::operator^(const int &other) const
{
    return Rational(pow(p, other), pow(q, other));
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
    std::cout << "inverse " << p << "/" << q << std::endl;
    auto g = Rational(q, p);
    std::cout << "outverse" << std::endl;
    return g;
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
    Rational x{base.p, base.q};
    p = pp;
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
    return RPR(r.isNonNegative(), r.abs(), 1);
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

bool RPR::operator<(const RPR &other) const
{
    if (sigma != other.sigma)
    {
        return other.sigma;
    }
    auto d = *this / other;
    return sigma ? d.x < one_rational : one_rational < d.x;
}

bool RPR::operator<=(const RPR &other) const
{
    return ((*this) < other) || (*this == other);
}

bool RPR::isNonNegative() const { return sigma; }

RPR RPR::operator+(const RPR &other) const
{
    std::cout << "zizsxinwz" << std::endl;
    // if (*this == -other)
    // {
    //     return zero_rpr;
    // }
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
        auto r = a.toRational();
        std::cout << "*******************" << std::endl;
        auto p = RPR::fromRational(one_rational + r);
        return p * (*this);
    }
    throw std::logic_error("Should be unreachable");
}

RPR RPR::operator*(const RPR &other) const
{
    // TODO: not correct if zero
    bool s = (sigma == other.sigma); // sign of the product
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    if (other == one_rpr)
    {
        return *this;
    }
    if (*this == one_rpr)
    {
        return *this;
    }
    if (other == zero_rpr || *this == zero_rpr)
    {
        return zero_rpr;
    }
    if (x == other.x)
    {
        auto r = Rational(1, p) + Rational(1, other.p);
        return RPR(s, x ^ r.p, r.q);
    }
    if (x == other.x.inverse())
    {
        auto r = Rational(1, p) - Rational(1, other.p);
        return RPR(s, x ^ r.p, r.q);
    }
    if (p == other.p)
    {
        return RPR(s, x * other.x, p);
    }
    throw std::domain_error("RPRs unable to be multiplied");
}

RPR RPR::operator*(const int &other) const
{
    return *this * RPR::fromInt(other);
}

RPR RPR::operator-(const RPR &other) const
{
    return (*this) + (-other);
}

RPR RPR::operator-() const
{
    return RPR(not sigma, x, p);
}

RPR RPR::abs() const
{
    return RPR(true, x, p);
}

RPR RPR::inverse() const
{
    std::cout << x.p << " " << x.q << std::endl;
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

Rational ampl::RPR::toRational() const
{
    if (not isRational())
    {
        throw std::domain_error("RPR is not rational");
    }
    return sigma ? x : -x;
}

real ampl::absReal(const real x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

real ampl::realFromInt(const int i)
{
    return static_cast<float>(i);
}

float ampl::realFromRational(const Rational r)
{
    return static_cast<float>(r.p) / static_cast<float>(r.q);
}

float ampl::realFromRPR(const RPR rpr)
{
    float f = pow(static_cast<float>(rpr.x.p) / static_cast<float>(rpr.x.q),
                  1. / static_cast<float>(rpr.p) / static_cast<float>(rpr.p));
    if (rpr.isNonNegative())
    {
        return f;
    }
    return -f;
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

Amplitude Amplitude::operator*(const real &other) const
{
    return Amplitude(re * other, im * other);
}

Amplitude Amplitude::operator*(const int &other) const
{
    return *this * Amplitude(other);
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

real Amplitude::square_module() const
{
    return (re * re) + (im * im);
}

real Amplitude::surface() const
{
    return absReal(re) * absReal(im);
}

Amplitude ampl::Amplitude::random()
{
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float i = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return Amplitude();
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
