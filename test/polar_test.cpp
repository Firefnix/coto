#include <gtest/gtest.h>

#include <polar.h>

using namespace polar;

class PolarTest : public testing::Test
{
public:
    PositiveInterval pa = (5.);
    PositiveInterval pb = (3., 4.);
    AngleInterval ra = (-.25, .2);
    AngleInterval rb = (3);
    Interval i1 = Interval(pa, ra);
    Interval i2 = Interval(pb, rb);
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