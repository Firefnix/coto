#ifndef POLAR_H
#define POLAR_H 1

typedef float real;

class PositiveInterval
{
public:
    PositiveInterval(real a, real b);

    PositiveInterval(real a);

    PositiveInterval operator+(PositiveInterval other);

    PositiveInterval operator*(PositiveInterval other);

protected:
    real min;
    real max;
};

class RemaindedInterval
{
public:
    RemaindedInterval(real a, real b);

    RemaindedInterval(real a);

    RemaindedInterval operator+(RemaindedInterval other);

    RemaindedInterval operator*(RemaindedInterval other);

    bool remainder;

protected:
    real min;
    real max;
    void set_remainder();
};

class PolarInterval
{
public:
    PolarInterval(PositiveInterval mod, RemaindedInterval arg);

    static PolarInterval singleton(real modulus, real argument);

    PolarInterval operator*(PolarInterval other);

protected:
    PositiveInterval mod;

    RemaindedInterval arg;
};

#endif