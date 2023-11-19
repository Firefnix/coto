#include "calc.h"
#include <iostream>
#include <exception>

class NumberNotImplemented : public std::runtime_error
{
public:
    NumberNotImplemented(std::string method)
        : runtime_error("Method Number::" + method + " is not supported") {}
};

/**
 * TYPING methods
 */

NT Number::type() const
{
    return NT::Other;
}

Integer Number::toInteger() const
{
    throw NumberNotImplemented("toInteger");
}

Rational Number::toRational() const
{
    throw NumberNotImplemented("toRational");
}

/**
 * OPERATING methods (+, *, (-), -, /, abs, sign, simple)
 */

Number Number::operator+(const Number &other) const
{
    if (other.type() != NT::Other)
    {
        return other + (*this);
    }
    throw NumberNotImplemented("operator+");
}

Number Number::operator*(const Number &other) const
{
    if (other.type() != NT::Other)
    {
        return other * (*this);
    }
    throw NumberNotImplemented("operator*");
}

Number Number::operator-() const
{
    return Integer(-1) * (*this);
}

Number Number::operator-(const Number &other) const
{
    return (*this).simple() + (-other);
}

Number Number::operator/(const Number &other) const
{
    return *this * other.inverse();
}

Number Number::abs() const
{
    throw NumberNotImplemented("abs");
};

Number Number::inverse() const
{
    throw NumberNotImplemented("inverse");
}

int Number::sign() const
{
    throw NumberNotImplemented("sign");
}

Number Number::simple() const
{
    throw NumberNotImplemented("simple");
};

/**
 * TESTING methods (z, ==, >=, <=, >, <)
 */
bool Number::isZero() const
{
    throw NumberNotImplemented("isZero");
}

bool Number::operator==(const Number &other) const
{
    throw NumberNotImplemented("operator==");
}

bool Number::operator!=(const Number &other) const
{
    return not(*this == other);
}

bool Number::operator>=(const Number &other) const
{
    return (*this - other).sign() == 1;
};

bool Number::operator<=(const Number &other) const
{
    return (*this - other).sign() == -1;
};

bool Number::operator>(const Number &other) const
{
    Number d = *this - other;
    return (not d.isZero()) && d.sign() == 1;
};

bool Number::operator<(const Number &other) const
{
    Number d = *this - other;
    return (not d.isZero()) && d.sign() == -1;
};
