#include <gtest/gtest.h>
#include <amplitude.h>

using namespace ampl;

TEST(AmplitudeTest, TestRational)
{
    rational z = rat_int(0);
    EXPECT_EQ(z.p, zero_rational.p);
    EXPECT_EQ(z.q, zero_rational.q);
    EXPECT_EQ(z, zero_rational);
    EXPECT_NE(&z, &zero_rational);
    rational x = {1, 2};
    EXPECT_NE(z, x);
}

TEST(AmplitudeTest, TestRPR)
{
    RPR one = RPR(true, {1, 1}, {1, 1});
    RPR another_one = rpr_int(1);
    RPR a_third_one = rpr_int(1);
    RPR mone = rpr_int(-1);
    EXPECT_EQ(one, another_one);
    EXPECT_EQ(one, a_third_one);
    EXPECT_EQ(another_one, a_third_one);
    EXPECT_NE(one, mone);
    EXPECT_EQ(one.opposite(), mone);
}

TEST(AmplitudeTest, TestMain)
{
    Amplitude i = Amplitude(rpr_int(2), rpr_int(1));
    Amplitude mi = Amplitude(rpr_int(2), rpr_int(-1));
    Amplitude k = i.conj();
    EXPECT_NE(i, k);
    EXPECT_EQ(k.re, mi.re);
    EXPECT_EQ(k.im, mi.im);
    EXPECT_EQ(k, mi);
}
