#include <gtest/gtest.h>
#include <qdd.h>
#include <iostream>

using namespace qdd;

class QDDTest : public testing::Test
{
public:
    QDD empty = QDD();

    struct status_vector<2> a =
    {
        ampl::zero, ampl::one
    };
    struct status_vector<4> p =
    {
        .values = {
            ampl::zero,
            ampl::one,
            ampl::zero,
            ampl::zero
        }
    };
    struct status_vector<8> b =
    {
        .values = { ampl::zero,
                    ampl::one,
                    ampl::zero,
                    ampl::zero,
                    ampl::zero,
                    ampl::zero,
                    ampl::zero,
                    ampl::zero }
    };

    Node test1Node = Node({{{6}, uptr}, {{0, 2}, uptr}, {{2, -1}, uptr}},
                          {{{8}, uptr}});

    QDD test1QDD = QDD(test1Node);
};

TEST_F(QDDTest, testConstructors)
{
    EXPECT_EQ(empty.root_ampl, ampl::one);
    EXPECT_TRUE(empty.root.isUnity());
}

TEST_F(QDDTest, testDepth)
{
    EXPECT_EQ(empty.root.depth(), 0);
    EXPECT_EQ(empty.depth(), 0);
    EXPECT_EQ(test1Node.depth(), 1) << test1Node.left.size();
    EXPECT_EQ(test1QDD.depth(), 1);
}

TEST_F(QDDTest, testFromStatusVector)
{
    auto d = QDD::fromStatusVector(a);
    std::cout << "Before e" << std::endl;
    auto e = QDD::fromStatusVector(p);
    std::cout << "After e" << std::endl;
    EXPECT_EQ(d.depth(), 1);
    EXPECT_EQ(d.root_ampl, ampl::one);
    EXPECT_EQ(d.root.countLeft(), 1);
    EXPECT_EQ(d.root.countRight(), 1);
    for (unsigned i = 0; i < pow(2, d.depth()); i++)
    {
        EXPECT_EQ(d.getAt(i), a.values[i]) << "Failed at index " << i;
    }
    // EXPECT_EQ(e.depth(), 2) << "Failed e.depth";
    EXPECT_EQ(e.root.countLeft(), 1);
    child c = e.root.left.back();
    EXPECT_EQ(c.x, ampl::one);
    EXPECT_EQ(c.n->countLeft(), 7) << c.n;
    // EXPECT_EQ(f.x, ampl::zero);

    // EXPECT_EQ(e.depth(), 3);
    // EXPECT_EQ(e.root_ampl, ampl::one);
    // EXPECT_EQ(e.root.countLeft(), 1);
    // EXPECT_EQ(e.root.countRight(), 1);
    // for (unsigned i = 0; i < pow(2, e.depth()); i++)
    // {
    //     EXPECT_EQ(e.getAt(i), ampl::zero) << "Failed at index " << i;
    // }
}

// TEST_F(QDDTest, MainTest)
// {
//     QDD d = QDD();
//     EXPECT_TRUE(d.root.is_unity());
//     EXPECT_EQ(d.depth(), 0);
// }
