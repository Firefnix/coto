#include <gtest/gtest.h>
#include <lang.h>

TEST(LangTest, Basics)
{
    A a;
    B x(1);
    EXPECT_EQ(a.value(), -1);
    EXPECT_EQ(x.value(), 1);
    A y = x.check(a);
    EXPECT_EQ(y.value(), 2);
    A z = y.check(y);
    EXPECT_EQ(z.value(), 3);
}