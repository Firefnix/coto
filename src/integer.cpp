#include <calc.h>
#include <iostream>

NT Integer::type() const
{
    return NT::Integer;
}

Integer Integer::toInteger() const
{
    return *this;
}

Rational Integer::toRational() const
{
    return Rational(n, 1);
};

/**
 * OPERATING methods
 */

int Integer::absolute(int n)
{
    return (n < 0) ? -n : n;
}

Number Integer::operator+(const Number &other) const
{
    std::cout << "In" << std::endl;
    switch (other.type())
    {
    case NT::Integer:
        std::cout << "Still In" << std::endl;
        return Integer(n + other.toInteger().n);
    case NT::Rational:
        return this->toRational() + other;
    default:
        std::cout << "Twoup" << std::endl;
        throw "impossible++";
    }
}

Number Integer::operator*(const Number &other) const
{
    switch (other.type())
    {
    case NT::Integer:
        return Integer(n * other.toInteger().n);
    case NT::Rational:
        return this->toRational() * other;
    default:
        throw "impossible**";
    }
}

Number Integer::abs() const
{
    return Integer(Integer::absolute(n));
}

Number Integer::inverse() const
{
    return Rational(1, n).simple();
}

int Integer::sign() const
{
    return (n >= 0) ? 1 : -1;
}

Number Integer::simple() const {
    return *this;
}

/* TESTING methods (izZero, ==) */

bool Integer::isZero() const
{
    return n == 0;
}

bool Integer::operator==(const Number &other) const
{
    std::cout << "Entering ==";
    std::cout << (this->type() == NT::Integer ? '1' : '2');
    switch (other.type())
    {
    case NT::Integer:
        std::cout << "Yes";
        return n == other.toInteger().n;
    default:
        std::cout << (other.type() == NT::Other ? '1' : '2');
        return false;
    }
}
