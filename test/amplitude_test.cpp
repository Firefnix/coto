#include <gtest/gtest.h>
#include <amplitude.h>

TEST(AmplitudeTest, TestPowLog2)
{
    EXPECT_EQ(pow2(0), 1);
    EXPECT_EQ(pow2(5), 32);
    EXPECT_EQ(pow2(10), 1024);
}

TEST(AmplitudeTest, random)
{
    std::vector<ampl::Amplitude> values;
    for (auto i = 0; i < 500; i++) {
        auto a = ampl::random();
        EXPECT_GE(abs(a), 0);
        EXPECT_LE(abs(a), 1);
        for (auto j = 0; j < i; j++) {
            EXPECT_NE(values.at(j), a)
                << "Got the same value" << ampl::to_string(a)
                << " at indexes " << j << " and " << i;
        }
        values.push_back(a);
    }
}

TEST(AmplitudeTest, randomizeState)
{
    ampl::State<1 << 6> state;
    EXPECT_EQ(state.at(0), state.at(1));
    EXPECT_NO_THROW(ampl::randomizeState(state));
    for (auto i = 0; i < (1 << 6); i++) {
        for (auto j = 0; j < i; j++) {
            EXPECT_NE(state.at(i), state.at(j));
        }
    }
}