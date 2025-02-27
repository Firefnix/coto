#include <gtest/gtest.h>
#include <selection.h>

static bool areMergeesSame(struct selection::mergees &m1, struct selection::mergees &m2);

class SelectionTest : public testing::Test
{
public:
    Diagram *leaf = new Diagram(0);
    Diagram *eig0 = new Diagram(1);
    Diagram *eig1 = new Diagram(1);
    Diagram *dgm = new Diagram(2);
};

TEST_F(SelectionTest, Random)
{
    eig0->lefto(leaf);
    eig1->righto(leaf);
    dgm->lefto(eig0);
    dgm->righto(eig1, 2.);
    EXPECT_EQ(dgm->countNodesAtHeight(1), 2);

    struct selection::mergees expectedMergees
    {
        eig0, eig1
    };
    struct selection::mergees m = selection::getMergeesAtHeight(1, *dgm, selection::MergeesChoiceStrategy::RANDOM);
    EXPECT_EQ(m.a->height, eig0->height);
    EXPECT_EQ(m.b->height, eig0->height);
    EXPECT_TRUE(areMergeesSame(expectedMergees, m));
}

static bool areMergeesSame(struct selection::mergees &m1, struct selection::mergees &m2)
{
    return (m1.a == m2.a && m1.b == m2.b) || (m1.a == m2.b && m1.b == m2.a);
}
