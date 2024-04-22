#include <gtest/gtest.h>
#include <diagram.h>

class DiagramTest : public testing::Test
{
public:
    Diagram<0> *leaf = new Diagram<0>();
    Diagram<1> *eig0 = new Diagram<1>();
    Diagram<2> *dgm = new Diagram<2>();
};

TEST_F(DiagramTest, testEvaluate)
{
    eig0->lefto(leaf);
    dgm->lefto(eig0);
    dgm->righto(eig0, absi::Interval::real(2.));
    absi::Interval a = leaf->evaluate()[0];
    absi::Interval b = eig0->evaluate()[0];
    absi::Interval c = eig0->evaluate()[1];
    EXPECT_EQ(absi::one, a);
    EXPECT_EQ(absi::one, b) << b.to_string();
    EXPECT_EQ(absi::zero, c);
}

TEST_F(DiagramTest, testConstruction)
{
    auto two = absi::Interval::real(2.);
    eig0->lefto(leaf);
    dgm->lefto(eig0);
    dgm->righto(eig0, two);
    auto vec = dgm->evaluate();
    EXPECT_EQ(absi::one, vec[0]);
    EXPECT_EQ(absi::zero, vec[1]);
    EXPECT_EQ(two, vec[2]) << vec[2].to_string() << dgm->right[0].x.to_string();
    EXPECT_EQ(absi::zero, vec[3]) << vec[3].to_string();
}
