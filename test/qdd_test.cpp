#include <gtest/gtest.h>
#include <qdd.h>

using namespace qdd;

class QDDTest : public testing::Test
{
public:
    struct status_vector<2> a =
    {
        .values = { ampl::zero,
                    ampl::one }
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

private:
    QDD createTestDiagram()
    {
        auto p = QDD();
        p.root = Node({{{6}, &u}, {{0, 2}, &u}, {{2, -1}, &u}},
                      {{{8}, &u}});
        return p;
    }
};

// TEST_F(QDDTest, FromStatusVector)
// {
//     auto d = QDD::fromStatusVector(a);
//     // auto e = QDD::fromStatusVector(b);
//     for (unsigned i = 0; i < 8; i++)
//     {
//         // EXPECT_EQ(d.getAt(i), a.values[i]);
//     }
//     EXPECT_EQ(d.depth(), 1);
//     // EXPECT_EQ(e.depth(), 3);
// }

// TEST_F(QDDTest, Sizes)
// {
//     EXPECT_TRUE(true);
//     // EXPECT_EQ(sizeof(child), 200);
//     // EXPECT_EQ(Node::unity().size(), );
// }

// // TEST_F(QDDTest, MainTest)
// // {
// //     QDD d = QDD();
// //     EXPECT_TRUE(d.root.is_unity());
// //     EXPECT_EQ(d.depth(), 0);
// // }
