#include <gtest/gtest.h>
#include <calc.h>

class IntegerTest : public testing::Test
{
public:
  Integer two{2}, mtwo{-2}, three{3}, five{5}, msix{-6};
};

TEST(NumberTest, SizeAndValue)
{
  Number n;
  EXPECT_EQ(sizeof n, 8);
}

TEST_F(IntegerTest, Value)
{
  EXPECT_EQ(zero.n, 0);
  EXPECT_EQ(one.n, 1);
  EXPECT_EQ(five.n, 5);
  EXPECT_EQ(mtwo.n, -2);
}

TEST_F(IntegerTest, Equal)
{
  Integer a(3);
  EXPECT_EQ(three, three);
  EXPECT_EQ(three, a);
  EXPECT_NE(three, zero);
}

TEST_F(IntegerTest, ToInteger)
{
  EXPECT_EQ(zero, zero.toInteger());
  EXPECT_EQ(one, one.toInteger());
  EXPECT_EQ(mtwo, mtwo.toInteger());
  EXPECT_EQ(mtwo.toInteger().n, -2);
  Integer a{5 + mtwo.toInteger().n};
  EXPECT_EQ(a.n, 3);
  EXPECT_EQ(three, a);
}

TEST_F(IntegerTest, Sum)
{
  EXPECT_TRUE(true);
  // std::cout << "Here" << std::endl;
  auto x = (zero + zero);
  // EXPECT_EQ(x.type(), NT::Integer);
  EXPECT_EQ(zero.type(), NT::Integer);
  // EXPECT_EQ(x.toInteger().n, 1);
  // EXPECT_EQ(x, zero);
  // EXPECT_EQ(one + one + one, three);
  // EXPECT_EQ(zero + three, three);
  // EXPECT_EQ(three + two, five);
  // EXPECT_EQ(two + three, five);
  // EXPECT_EQ(three + zero, three);
  // EXPECT_EQ(three + zero, three);
}

TEST_F(IntegerTest, Difference)
{
  EXPECT_TRUE(true);
  // EXPECT_EQ(-zero, zero);
  // EXPECT_EQ(zero - zero, zero);
  // EXPECT_EQ(one - one, zero);
  // EXPECT_EQ(three - zero, three);
  // EXPECT_EQ(three - two, one);
  // EXPECT_EQ(two + three, five);
  // EXPECT_EQ(three + zero, three);
  // EXPECT_EQ(three + zero, three);
  // EXPECT_EQ(-zero, zero);
}

TEST_F(IntegerTest, Product)
{
  EXPECT_TRUE(true);
  // Number x = zero * Integer{-1};
  // EXPECT_NE(x.type(), NT::Other);
  // EXPECT_EQ(x.toInteger().n, 0);
  // EXPECT_EQ(x, zero);

  // EXPECT_EQ(one * zero, zero);
  // EXPECT_EQ(one * one, one);
  // EXPECT_EQ(one * mtwo, mtwo);
  // EXPECT_EQ(three * one, three);
  // EXPECT_EQ(mtwo * three, msix);
  // EXPECT_EQ(three * mtwo, msix);
}
