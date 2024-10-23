#include <gtest/gtest.h>
#include <selection.h>

template <size_t h>
static bool areMergeesSame(struct selection::mergees<h>& m1, struct selection::mergees<h>& m2);

class SelectionTest : public testing::Test
{
public:
    Diagram<0> *leaf = new Diagram<0>();
    Diagram<1> *eig0 = new Diagram<1>();
    Diagram<1> *eig1 = new Diagram<1>();
    Diagram<2> *dgm = new Diagram<2>();
};

TEST_F(SelectionTest, Random)
{
    eig0->lefto(leaf);
    eig1->righto(leaf);
    dgm->lefto(eig0);
    dgm->righto(eig0, absi::Interval::real(2.));
    struct selection::mergees<1> expectedMergees {eig0, eig1};
    struct selection::mergees<1> m = selection::getMergeesAtHeight<1, 2>(*dgm, selection::MergeesChoiceStrategy::RANDOM);
    EXPECT_TRUE(areMergeesSame(expectedMergees, m));
}

template <size_t h>
static bool areMergeesSame(struct selection::mergees<h>& m1, struct selection::mergees<h>& m2)
{
    return (m1.a == m2.a && m1.b == m2.b)
        || (m1.a == m2.b && m1.b == m2.a);
}
