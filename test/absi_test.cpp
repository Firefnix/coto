#include <gtest/gtest.h>
#include <absi.h>

class AbsiTest : public testing::Test
{
public:
    cartesian::Interval a = cartesian::Interval(ampl::one);
    cartesian::Interval b = cartesian::Interval(ampl::zero, ampl::one + ampl::i);
};

TEST_F(AbsiTest, Surface)
{
    EXPECT_EQ(a.norm(), ampl::zero_real);
    EXPECT_EQ(b.norm(), ampl::sqrt2);
}

TEST_F(AbsiTest, Contains)
{
    EXPECT_TRUE(a.contains(ampl::one));
    EXPECT_FALSE(a.contains(ampl::i));
    EXPECT_TRUE(b.contains(ampl::i));
    EXPECT_FALSE(b.contains(ampl::i * 3.));
}

class PolarTest : public testing::Test
{
public:
    polar::PositiveInterval pa = (5.);
    polar::PositiveInterval pb = (3., 4.);
    polar::AngleInterval ra = (-.25, .2);
    polar::AngleInterval rb = (3);
    polar::Interval i1 = polar::Interval(pa, ra);
    polar::Interval i2 = polar::Interval(pb, rb);
};

TEST_F(PolarTest, testPositiveInterval)
{
    EXPECT_NO_THROW(pa + pb);
    EXPECT_NO_THROW(pa * pb);
    EXPECT_NO_THROW(pa | pb);
}

TEST_F(PolarTest, testRemaindedInterval)
{
    EXPECT_NO_THROW(ra + rb);
    EXPECT_NO_THROW(ra * rb);
    EXPECT_NO_THROW(ra | rb);
}

TEST_F(PolarTest, testInterval)
{
    EXPECT_NO_THROW(i1 * i2);
    EXPECT_NO_THROW(i1 | i2);
}