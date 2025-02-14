#include <gtest/gtest.h>
#include <gateappliers.h>

const size_t MAX_QUBITS = 8;

size_t flipNthBit(const size_t n, const size_t index)
{
    return index ^ (1 << n);
}

class GateAppliersTest : public testing::Test
{
public:
    Diagram *leaf = new Diagram(0);
    Diagram *eig0 = Diagram::eig0(1);
    Diagram *eig1 = new Diagram(1);
    Diagram *dgm = new Diagram(2);
};

TEST_F(GateAppliersTest, X)
{
    for (auto numberOfQubits = 1; numberOfQubits < MAX_QUBITS; numberOfQubits++)
    {
        for (auto qubitToApplyXOn = 0; qubitToApplyXOn < numberOfQubits; qubitToApplyXOn++)
        {
            PowArray<ampl::Amplitude> base(numberOfQubits);
            for (auto i = 0; i < base.size(); i++)
            {
                base[i] = i;
            }
            Evaluation result(numberOfQubits);
            for (auto i = 0; i < result.size(); i++)
            {
                result[flipNthBit(numberOfQubits - qubitToApplyXOn - 1, i)] = Interval::real(i);
            }

            auto d = Diagram::fromStateVector(base);
            gateappliers::applyX(d, qubitToApplyXOn);

            auto ev = d->evaluate();
            for (auto i = 0; i < result.size(); i++)
            {
                EXPECT_EQ(ev[i], result[i])
                    << "Failed appplying X on qubit " << qubitToApplyXOn
                    << " at index " << i
                    << " got " << ev[i].to_string()
                    << ", expected " << result[i].to_string();
            }
        }
    }
}

TEST_F(GateAppliersTest, phase)
{
    for (auto numberOfQubits = 1; numberOfQubits < MAX_QUBITS; numberOfQubits++)
    {
        for (auto qubitToApplyPhaseOn = 0; qubitToApplyPhaseOn < numberOfQubits; qubitToApplyPhaseOn++)
        {
            const auto phaseDenominator = 3;
            ampl::ConcreteState base(numberOfQubits);
            for (auto i = 0; i < base.size(); i++)
            {
                base[i] = i;
            }
            Evaluation expected(numberOfQubits);
            for (auto i = 0; i < expected.size(); i++)
            {
                expected[i] = !(i & (1 << (numberOfQubits - qubitToApplyPhaseOn - 1)))
                                  ? absi::Interval::real(i)
                                  : polar::Interval(polar::PositiveInterval(i), polar::AngleInterval(2. / phaseDenominator, 0));
                std::cout << expected[i].to_string() << std::endl;
            }

            auto d = Diagram::fromStateVector(base);
            gateappliers::applyPhase(d, qubitToApplyPhaseOn, phaseDenominator);

            auto ev = d->evaluate();
            std::cout << "At height " << qubitToApplyPhaseOn << ", got " << d->countNodesAtHeight(qubitToApplyPhaseOn) << std::endl;
            for (auto i = 0; i < expected.size(); i++)
            {
                EXPECT_EQ(ev[i], expected[i])
                    << "Failed appplying phase(2*pi/" << phaseDenominator
                    << ") on qubit " << qubitToApplyPhaseOn
                    << " at index " << i
                    << " got result " << ev[i].to_string()
                    << ", while expected " << expected[i].to_string();
            }
            std::cout << "--------" << std::endl;
        }
    }
}

TEST_F(GateAppliersTest, gateMatrixIdentity)
{
    for (auto numberOfQubits = 1; numberOfQubits < MAX_QUBITS; numberOfQubits++)
    {
        for (auto qubitToApplyIdentityOn = 0; qubitToApplyIdentityOn < numberOfQubits; qubitToApplyIdentityOn++)
        {
            gateappliers::GateMatrix id(1);
            id(0, 0) = Interval::real(1);
            id(1, 1) = Interval::real(1);

            ampl::ConcreteState base(numberOfQubits);
            for (auto i = 0; i < base.size(); i++)
            {
                base[i] = i;
            }

            auto d = Diagram::fromStateVector(base);
            gateappliers::applyGateMatrix(d, qubitToApplyIdentityOn, id);

            auto ev = d->evaluate();
            for (auto i = 0; i < base.size(); i++)
            {
                EXPECT_EQ(ev[i], Interval::singleton(base[i]))
                    << "Failed appplying identity on qubit 0"
                    << " at index " << i
                    << " got " << ev[i].to_string()
                    << ", expected " << base[i];
            }
        }
    }
}

TEST_F(GateAppliersTest, gateMatrixHadamardOnQubit0)
{
    auto m = gateappliers::GateMatrix(1);
    m(0, 0) = 1;
    m(0, 1) = 1;
    m(1, 0) = 1;
    m(1, 1) = -1;

    ampl::Amplitude v[] = {1, 2, 3, 4};
    ampl::ConcreteState base(2, v);

    auto d = Diagram::fromStateVector(base);

    gateappliers::applyGateMatrix(d, 0, m);

    auto ev = d->evaluate();
    EXPECT_EQ(ev[0], Interval::real(4)) << ev[0].to_string() << " != 4";
    EXPECT_EQ(ev[1], Interval::real(6)) << ev[1].to_string() << " != 6";
    EXPECT_EQ(ev[2], Interval::real(-2)) << ev[2].to_string() << " != -2";
    EXPECT_EQ(ev[3], Interval::real(-2)) << ev[3].to_string() << " != -2";
}

TEST_F(GateAppliersTest, gateMatrixHadamardOnQubit1)
{
    absi::Interval v[] = {1, 1, 1, -1};
    gateappliers::GateMatrix m(1, v);

    ampl::ConcreteState base(3);
    for (auto i = 0; i < base.size(); i++)
    {
        base[i] = i + 1;
    }

    auto d = Diagram::fromStateVector(base);
    gateappliers::applyGateMatrix(d, 1, m);
    auto computed = d->evaluate();

    ampl::Amplitude expected[8] = {4, 6, -2, -2, 12, 14, -2, -2};
    for (auto i = 0; i < 8; i++)
    {
        EXPECT_EQ(computed[i], Interval::singleton(expected[i]))
            << "Failed applying H on qubit 1 at index " << i
            << ", computed " << computed[i].to_string()
            << ", expected " << expected[i];
    }
}

TEST_F(GateAppliersTest, applyH)
{
    auto h = gateappliers::GateMatrix(1);
    h(0, 0) = ampl::invSqrt2;
    h(0, 1) = ampl::invSqrt2;
    h(1, 0) = ampl::invSqrt2;
    h(1, 1) = -ampl::invSqrt2;

    const auto numberOfQubits = 4;
    for (auto q = 0; q < numberOfQubits; q++)
    {
        auto d0 = Diagram::randomPointer(numberOfQubits);
        auto d1 = d0->clone();
        gateappliers::applyGateMatrix(d0, q, h);
        gateappliers::applyH(d1, q);

        auto e0 = d0->evaluate();
        auto e1 = d1->evaluate();
        for (auto i = 0; i < e0.size(); i++)
        {
            EXPECT_EQ(e0[i], e1[i])
                << "Failed applying H on qubit " << q << "  at index " << i
                << ", e0 " << e0[i].to_string()
                << ", e1 " << e1[i].to_string();
        }
    }
}
