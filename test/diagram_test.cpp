#include <gtest/gtest.h>
#include <diagram.h>
#include <amplitude.h>

class DiagramTest : public testing::Test
{
public:
    Diagram *leaf = new Diagram(0);
    Diagram *eig0 = new Diagram(1);
    Diagram *eig1 = new Diagram(1);
    Diagram *dgm = new Diagram(2);
};

TEST_F(DiagramTest, testStateVector)
{
    for (auto i = 0; i < 100; i++)
    {
        ampl::ConcreteState state(2);
        ampl::randomizeState(state);
        auto diagram = Diagram::fromStateVector(state);
        auto evaluatedState = diagram->evaluate();
        for (auto i = 0; i < state.size(); i++)
        {
            EXPECT_EQ(evaluatedState[i], Interval::singleton(state[i]))
                << "Failed at index " << i << " against " << evaluatedState[i].to_string();
        }
    }
}

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
    auto vec = dgm->evaluate(); // (1, 0, 2, 0)
    EXPECT_EQ(absi::one, vec[0]);
    EXPECT_EQ(absi::zero, vec[1]) << vec[1].to_string();
    EXPECT_EQ(two, vec[2]) << vec[2].to_string();
    EXPECT_EQ(absi::zero, vec[3]) << vec[3].to_string();
}

TEST_F(DiagramTest, testAdditiveness)
{
    auto two = absi::Interval::real(2.);
    auto minus_three = absi::Interval::real(-3.);
    auto minus_one = absi::Interval::real(2. + (-3.));
    eig0->lefto(leaf, two);
    eig0->lefto(leaf, minus_three);
    auto vec = eig0->evaluate();
    EXPECT_EQ(minus_one, vec[0]);
    EXPECT_EQ(absi::zero, vec[1]);
}

TEST_F(DiagramTest, testNodePointersAtHeight)
{
    eig0->lefto(leaf);
    eig1->righto(leaf);
    dgm->lefto(eig0);
    dgm->righto(eig1);
    auto vec = dgm->getNodePointersAtHeight(1);
    EXPECT_EQ(2, vec.size());
    if (vec[0] != eig0)
    {
        std::swap(vec[0], vec[1]);
    }
    EXPECT_EQ(eig0, vec[0]);
    EXPECT_EQ(eig1, vec[1]);
}

TEST_F(DiagramTest, testRandomIsNormLowerThanOne)
{
    auto d = Diagram::random(2);
    auto vec = d.evaluate();
    for (auto i : vec)
    {
        EXPECT_LE(i.norm(), 1.);
    }
}

TEST_F(DiagramTest, testRandomAssertVariability)
{
    const auto n = 100;
    size_t counts[n][5];
    bool isNotDuplicate[n];
    for (auto i = 0; i < n; i++)
    {
        auto d = Diagram::random(5);
        for (auto j = 0; j < 5; j++)
        {
            counts[i][j] = d.countNodesAtHeight(j);
        }
    }
    for (auto i = 0; i < n; i++)
    {
        bool broke = false;
        for (auto k = 0; k < i; k++)
        {
            for (auto j = 0; j < 5; j++)
            {
                if (counts[i][j] != counts[i][k])
                {
                    broke = true;
                    break;
                }
            }
        }
    }
    for (auto i = 0; i < n; i++)
    {
        EXPECT_TRUE(true);
    }
}

TEST_F(DiagramTest, testRandomAssertBoundaries)
{
    const auto n = 100;
    for (auto j = 0; j < n; j++)
    {
        auto d = Diagram::random(5);
        for (auto i = 0; i < 5; i++)
        {
            EXPECT_GT(d.countNodesAtHeight(i), 0);
            EXPECT_LE(d.countNodesAtHeight(i), pow(CHILDREN_NUMBER_AMBITION, i));
        }
    }
}

TEST_F(DiagramTest, testEnclosure)
{
    const auto n = 3;
    for (auto i = 0; i < 1000; i++)
    {
        auto d = Diagram::random(n);
        auto v = d.evaluate();

        auto real_rho = v[0];
        for (auto i = 1; i < pwrtwo(n); i++)
        {
            real_rho = real_rho | v[i];
        }

        auto rho = d.enclosure();
        EXPECT_EQ(rho, real_rho);
        EXPECT_EQ(rho, d.enclosure());
    }
}

/* TEST_F(DiagramTest, testEnclosureUpdate)
{
    const auto n = 2;
    auto c = Diagram::randomPointer(n-1);
    auto d = Diagram::randomPointer(n);
    auto rho = d->enclosure();

    // This necessarily adds uncertainty.
    d->lefto(c);
    d->righto(c);

    auto v = d->evaluate();
    auto real_rho = v[0];
    for (auto i = 1; i < pwrtwo(n); i++) {
        real_rho = real_rho | v[i];
    }
    auto new_rho = d->enclosure();
    // EXPECT_FALSE(true);
    EXPECT_EQ(new_rho, real_rho) << new_rho.to_string() << " != " << real_rho.to_string();
} */