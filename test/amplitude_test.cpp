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
    Rational u(1, 9), v(2, 18), w(-1, 2);
    Rational x(1, 2), y(-1, 3), z(1, 6);
    EXPECT_EQ(u, v);
    EXPECT_NE(z, x);
    EXPECT_EQ(x + y, z);
    EXPECT_EQ(u - v, zero_rational);
    EXPECT_EQ(-w, x);
    EXPECT_EQ(y * y, u);
    EXPECT_EQ(x / z, Rational::fromInt(3));
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
    RPR one_from_rational = RPR(true, one_rational, one_rational);
    EXPECT_EQ(one_from_rational, one);
}

TEST(AmplitudeTest, TestRPROperations)
{
    auto product = sqrt2_rpr * sqrt2_rpr;
    auto two = RPR::fromInt(2);
    EXPECT_EQ(product, two);
    EXPECT_FALSE((-sqrt2_rpr).isNonNegative());
}

TEST(AmplitudeTest, TestMain)
{
    Amplitude i = Amplitude(RPR::fromInt(2), RPR::fromInt(1));
    Amplitude mi = Amplitude(RPR::fromInt(2), RPR::fromInt(-1));
    Amplitude k = i.conj();
    EXPECT_NE(i, k);
    EXPECT_EQ(k, mi);
}

TEST(AmplitudeTest, TestPowLog2)
{
    EXPECT_EQ(pow2(0), 1);
    EXPECT_EQ(pow2(5), 32);
    EXPECT_EQ(pow2(10), 1024);
    EXPECT_NO_THROW(log2(0));
    EXPECT_EQ(log2(1), 0);
    EXPECT_EQ(log2(2), 1);
    EXPECT_EQ(log2(16), 4);
    EXPECT_EQ(log2(17), 4);
}