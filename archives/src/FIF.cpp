FIF FIF::operator+(const FIF &other) const
{
    return FIF(re + other.re, im + other.im);
}

FIF FIF::operator*(const FIF &other) const
{
    return FIF(re * other.re - im * other.im, re * other.im + im * other.re);
}

FIF FIF::operator*(const int &other) const
{
    return FIF(re * other, im * other);
}

FIF FIF::operator-(const FIF &other) const
{
    return FIF(re - other.re, im - other.im);
}

FIF FIF::operator-() const
{
    return FIF(-re, -im);
}
FIF FIF::operator+(const FIF &other) const
{
    return FIF(re + other.re, im + other.im);
}

FIF FIF::operator*(const FIF &other) const
{
    return FIF(re * other.re - im * other.im, re * other.im + im * other.re);
}

FIF FIF::operator*(const int &other) const
{
    return FIF(re * other, im * other);
}

FIF FIF::operator-(const FIF &other) const
{
    return FIF(re - other.re, im - other.im);
}

FIF FIF::operator-() const
{
    return FIF(-re, -im);
}
FIF FIF::operator+(const FIF &other) const
{
    return FIF(re + other.re, im + other.im);
}

FIF FIF::operator*(const FIF &other) const
{
    return FIF(re * other.re - im * other.im, re * other.im + im * other.re);
}

FIF FIF::operator*(const int &other) const
{
    return FIF(re * other, im * other);
}

FIF FIF::operator-(const FIF &other) const
{
    return FIF(re - other.re, im - other.im);
}

FIF FIF::operator-() const
{
    return FIF(-re, -im);
}
