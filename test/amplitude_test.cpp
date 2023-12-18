#include <gtest/gtest.h>
#include <amplitude.h>

using namespace ampl;

TEST(AmplitudeTest, TestRationalConstructors)
{
    auto a = Rational();
    EXPECT_EQ(a, zero_rational);
    EXPECT_NE(&a, &zero_rational);
    auto b = Rational(0, 1);
    EXPECT_EQ(b, zero_rational);
    EXPECT_NE(&b, &zero_rational);
    auto c = Rational(zero_rational);
    EXPECT_EQ(c, zero_rational);
    EXPECT_NE(&c, &zero_rational);
    auto d = Rational::fromInt(0);
    EXPECT_EQ(d, zero_rational);
    EXPECT_NE(&d, &zero_rational);
    EXPECT_THROW(Rational(1, 0), std::domain_error);
}

TEST(AmplitudeTest, TestRational)
{
    Rational l(1, 9), v(2, 18), w(-1, 2);
    Rational x(1, 2), y(-1, 3), z(1, 6);
    EXPECT_EQ(l, v);
    EXPECT_NE(z, x);
    EXPECT_EQ(x + y, z);
    EXPECT_EQ(l - v, zero_rational);
    EXPECT_EQ(-w, x);
    EXPECT_EQ(y * y, l);
    EXPECT_EQ(l.inverse(), Rational::fromInt(9));
    EXPECT_EQ(x / z, Rational::fromInt(3));
    EXPECT_EQ(one_rational.inverse(), one_rational);
}

TEST(AmplitudeTest, TestRPRConstructors)
{
    RPR one = RPR(true, one_rational, 1);
    RPR another_one = RPR::fromInt(1);
    RPR a_third_one = RPR::fromRational(one_rational);
    RPR mone = RPR::fromInt(-1);
    EXPECT_EQ(one, another_one);
    EXPECT_EQ(one, a_third_one);
    EXPECT_EQ(another_one, a_third_one);
    EXPECT_NE(one, mone);
    EXPECT_EQ(-one, mone);
    RPR one_from_rational = RPR(true, one_rational, 1);
    EXPECT_EQ(one_from_rational, one);
}

TEST(AmplitudeTest, TestRPROperations)
{
    auto product = sqrt2_rpr * sqrt2_rpr;
    EXPECT_TRUE(true);
    auto two = RPR::fromInt(2);
    EXPECT_EQ(product, two);
    EXPECT_FALSE((-sqrt2_rpr).isNonNegative());
    // EXPECT_EQ(one_rpr.x.p, 1);
    // EXPECT_EQ(one_rpr.x.q, 1);
    // EXPECT_EQ(one_rpr.inverse(), one_rpr);
}

// TEST(AmplitudeTest, TestRPRSum)
// {
//     auto a = RPR::fromRational(Rational(1, 3));
//     auto b = RPR::fromRational(Rational(-2, 5));
//     auto c = RPR::fromRational(Rational(-1, 15));
//     EXPECT_EQ(a + zero_rpr, a);
//     EXPECT_EQ(zero_rpr + b, b);
//     EXPECT_EQ(a + b, c);
//     EXPECT_EQ(c - a, b);
// }

// TEST(AmplitudeTest, TestMain)
// {
//     auto i = Amplitude::fromInts(2, 1);
//     auto mi = Amplitude::fromInts(2, -1);

//     Amplitude k = i.conj();
//     EXPECT_NE(i, k);
//     EXPECT_EQ(k, mi);
//     unsigned s = sizeof(i);
//     EXPECT_EQ(s, 112);
// }

TEST(AmplitudeTest, Product)
{
    auto l = Amplitude(2, 1);
    auto v = Amplitude(6, -4);
    auto w = Amplitude(16, -2);
    auto r = l * v;
    EXPECT_EQ(r.re, w.re);
    // EXPECT_EQ(r.im.sigma, false);
    // EXPECT_EQ(r.im.sigma, false);
    // auto s = one * 2 + i;
    // std::cout << "RE" << static_cast<float>(s.re) << " " << static_cast<float>(u.re) << std::endl;
    // std::cout << "IM" << static_cast<float>(s.im) << " " << static_cast<float>(u.im) << std::endl;
    // EXPECT_EQ(s, u);
}

// TEST(AmplitudeTest, TestPowLog2)
// {
//     EXPECT_EQ(pow2(0), 1);
//     EXPECT_EQ(pow2(5), 32);
//     EXPECT_EQ(pow2(10), 1024);
//     EXPECT_NO_THROW(log2(0));
//     EXPECT_EQ(log2(1), 0);
//     EXPECT_EQ(log2(2), 1);
//     EXPECT_EQ(log2(16), 4);
//     EXPECT_EQ(log2(17), 4);
// }
