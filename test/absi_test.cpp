#include <gtest/gtest.h>
#include <absi.h>

using namespace absi;

class AbsiTest : public testing::Test
{
public:
    AbstractElement a = AbstractElement(ampl::one);
    AbstractElement b = AbstractElement(ampl::zero, ampl::one + ampl::i);
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