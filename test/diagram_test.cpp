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
    absi::Interval i = leaf->evaluate()[0];
    EXPECT_EQ(absi::one, i);
}

TEST_F(DiagramTest, testConstruction)
{
    eig0->lefto(leaf);
    dgm->lefto(eig0);
    dgm->righto(eig0, absi::Interval::real(2.));
    // auto vec = dgm->evaluate();
    // EXPECT_EQ(vec[0], absi::);
}
// TEST_F(DiagramTest, test)