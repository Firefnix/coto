#include <gtest/gtest.h>
#include <absi.h>

class CartesianTest : public testing::Test
{
public:
    cartesian::Interval a = cartesian::Interval::singleton(ampl::one);
    cartesian::Interval b = cartesian::Interval(ampl::zero, ampl::one + ampl::i);
};

TEST_F(CartesianTest, Norm)
{
    EXPECT_EQ(a.norm(), ampl::zero_real);
    EXPECT_EQ(b.norm(), ampl::sqrt2);
}

TEST_F(CartesianTest, Contains)
{
    EXPECT_TRUE(a.contains(ampl::one));
    EXPECT_FALSE(a.contains(ampl::i));
    EXPECT_TRUE(b.contains(ampl::i));
    EXPECT_FALSE(b.contains(ampl::i * 3.));
}

TEST_F(CartesianTest, Equal)
{
    cartesian::Interval c = cartesian::Interval(ampl::zero, ampl::one + ampl::i);
    EXPECT_EQ(b, c);
}

TEST_F(CartesianTest, Join)
{
    auto j = cartesian::zero
    | cartesian::Interval::singleton(ampl::i + ampl::one);
    EXPECT_EQ(j, b);
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

TEST_F(PolarTest, PositiveInterval)
{
    EXPECT_NO_THROW(pa + pb);
    EXPECT_NO_THROW(pa * pb);
    EXPECT_NO_THROW(pa | pb);
}

TEST_F(PolarTest, AngleInterval)
{
    EXPECT_NO_THROW(ra + rb);
    EXPECT_NO_THROW(ra * rb);
    EXPECT_NO_THROW(ra | rb);
}

TEST_F(PolarTest, Operations)
{
    EXPECT_NO_THROW(i1 * i2);
    EXPECT_NO_THROW(i1 | i2);
}

TEST_F(PolarTest, PositiveIntervalCreation)
{
    auto x = 1.4;
    auto p = polar::PositiveInterval(x);
    EXPECT_EQ(p.min, x);
    EXPECT_EQ(p.max, x);
}

TEST_F(PolarTest, Add)
{
    auto mthree = polar::Interval::real(-3.);
    auto sum = polar::Interval::real(2.) + mthree;
    auto ref = polar::Interval::real(2. + (-3.));
    EXPECT_EQ(sum, ref) << sum.to_string() << " vs " << ref.to_string();
}

TEST_F(PolarTest, Norm)
{
    EXPECT_EQ(i1.norm(), 0.);
    EXPECT_EQ(i2.norm(), 0.);
}