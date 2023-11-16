#ifndef CALC_H_
#define CALC_H_ 1

#include <iostream>

enum class NT
{
    Integer,
    Rational,
    Other
};

class Integer;
class Rational;

// Implements a (complex) number
class Number
{
public:
    /* TYPING methods (type, toInteger, toRational) */
    virtual NT type() const;
    virtual Integer toInteger() const;
    virtual Rational toRational() const;

    /* OPERATING methods (+*--/abs) */
    virtual Number operator+(const Number &other) const;
    virtual Number operator*(const Number &other) const;
    Number operator-() const;
    Number operator-(const Number &other) const;
    virtual Number operator/(const Number &other) const;
    virtual Number abs() const;
    virtual Number inverse() const;
    virtual int sign() const;
    virtual Number simple() const;

    /* TESTING methods (z, ==, >=, <=, >, <) */
    virtual bool isZero() const;
    virtual bool operator==(const Number &other) const;
    bool operator>=(const Number &other) const;
    bool operator<=(const Number &other) const;
    bool operator>(const Number &other) const;
    bool operator<(const Number &other) const;
};

class Rational : public Number
{
public:
    Rational(int a, int b)
    {
        if (b == 0)
        {
            throw "Division by zero";
        }
        int d = Rational::gcd(a, b);
        p = a;
        q = b;
    }

    Rational(const Rational &obj)
    {
        p = obj.p;
        q = obj.q;
    }

    /* TYPING methods (type, toInteger, toRational) */
    NT type() const override;
    Integer toInteger() const override;
    Rational toRational() const override { return *this; };

    /* OPERATING methods (gcd, isZero, simple) */
    bool isZero() const override;
    Number simple() const override;

private:
    static int gcd(int, int);
    int p, q;
};

class Integer : public Number
{
public:
    int n;
    Integer(int k) { n = k; }
    Integer(const Integer &x) { n = x.n; }

    /* TYPING methods (type, toInteger, toRational) */
    NT type() const override;
    Integer toInteger() const override;
    Rational toRational() const override;

    /* OPERATING methods */
    static int absolute(int);
    Number operator+(const Number &other) const override;
    Number operator*(const Number &other) const override;
    Number abs() const override;
    Number inverse() const override;
    int sign() const override;
    Number simple() const override;

    /* Number */
    bool isZero() const override;
    bool operator==(const Number &other) const override;
};

static const Integer zero{0};
static const Integer one{1};

class OperationImpossible : public std::runtime_error
{
public:
    OperationImpossible(NT a, NT b, char c)
        : runtime_error("A number of type " + describe(a) + " cannot be " + c + "'ed to a" + describe(b)) {}

    std::string describe(NT t)
    {
        switch (t)
        {
        case NT::Integer:
            return "Integer";
        case NT::Rational:
            return "Rational";
        case NT::Other:
            return "Number(Other)";
        }
    }
};

#endif
