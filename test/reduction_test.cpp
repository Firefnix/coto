#include <gtest/gtest.h>
#include <reduction.h>

TEST(ReductionTest, cutDeadBranches)
{
    ampl::Amplitude v[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    auto d = diagram::Diagram::fromStateVector(ampl::ConcreteState(3, v));
    EXPECT_EQ(d->countNodesAtHeight(0), 0);
    EXPECT_EQ(d->countNodesAtHeight(1), 4);
    EXPECT_EQ(d->countNodesAtHeight(2), 2);
    EXPECT_EQ(d->countNodesAtHeight(3), 1);
    reduction::cutDeadBranches(d);
    EXPECT_EQ(d->countNodesAtHeight(0), 0);
    EXPECT_EQ(d->countNodesAtHeight(1), 0);
    EXPECT_EQ(d->countNodesAtHeight(2), 0);
    EXPECT_EQ(d->countNodesAtHeight(3), 1);
}
