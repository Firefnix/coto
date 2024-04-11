#include <gtest/gtest.h>
#include <qdd.h>

using namespace qdd;

class NodeTest : public testing::Test
{
public:
    std::shared_ptr<Node> node1_ptr = std::make_shared<Node>(Node({{{6}, uptr}, {{0, 2}, uptr}, {{2, -1}, uptr}},
                                                                  {{{8}, uptr}}));

    Node node1 = *node1_ptr;

    Node node2 = Node({{ampl::i, node1_ptr}}, {});
};

TEST_F(NodeTest, testConstructors)
{
    Node node1Copy = Node(node1);
    Node uCopy = Node(u);
    EXPECT_EQ(node1.isUnity(), node1Copy.isUnity());
    EXPECT_EQ(uCopy.isUnity(), u.isUnity());

    EXPECT_EQ(uCopy.countLeft(), u.countLeft());
    EXPECT_EQ(node1.countLeft(), node1Copy.countLeft());

    EXPECT_EQ(node1.depth(), node1Copy.depth());
    EXPECT_EQ(uCopy.depth(), u.depth());

    EXPECT_EQ(node1.countRight(), node1Copy.countRight());
    EXPECT_EQ(uCopy.countRight(), u.countRight());
}

TEST_F(NodeTest, testIsUnity)
{
    EXPECT_TRUE(u.isUnity());
    EXPECT_FALSE(node1.isUnity());
}

TEST_F(NodeTest, testCountLeft)
{
    EXPECT_EQ(u.countLeft(), 0);
    EXPECT_EQ(node1.countLeft(), 3);
    EXPECT_EQ(node2.countLeft(), 1);
}

TEST_F(NodeTest, testCountRight)
{
    EXPECT_EQ(u.countRight(), 0);
    EXPECT_EQ(node1.countRight(), 1);
    EXPECT_EQ(node2.countRight(), 0);
}

TEST_F(NodeTest, testDepth)
{
    EXPECT_EQ(u.depth(), 0);
    EXPECT_EQ(node1.depth(), 1);
    EXPECT_EQ(node2.depth(), 2);
}
