#include <gtest/gtest.h>
#include <reduction.h>

TEST(ReductionTest, cut_dead_branches)
{
    ampl::Amplitude v[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    auto d = diagram::Diagram::from_state_vector(ampl::ConcreteState(3, v));
    EXPECT_EQ(d->count_nodes_at_height(0), 0);
    EXPECT_EQ(d->count_nodes_at_height(1), 4);
    EXPECT_EQ(d->count_nodes_at_height(2), 2);
    EXPECT_EQ(d->count_nodes_at_height(3), 1);
    reduction::cut_dead_branches(d);
    EXPECT_EQ(d->count_nodes_at_height(0), 0);
    EXPECT_EQ(d->count_nodes_at_height(1), 0);
    EXPECT_EQ(d->count_nodes_at_height(2), 0);
    EXPECT_EQ(d->count_nodes_at_height(3), 1);
}
