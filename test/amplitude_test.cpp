#include <gtest/gtest.h>
#include <amplitude.h>

using namespace ampl;

TEST(AmplitudeTest, TestPowLog2)
{
    EXPECT_EQ(pow2(0), 1);
    EXPECT_EQ(pow2(5), 32);
    EXPECT_EQ(pow2(10), 1024);
}
