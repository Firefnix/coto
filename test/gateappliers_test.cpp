#include <gtest/gtest.h>
#include <gateappliers.h>

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
    for (auto numberOfQubits = 1; numberOfQubits < 9; numberOfQubits++)
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
                result[flipNthBit(numberOfQubits - qubitToApplyXOn - 1, i)] = absi::Interval::real(i);
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
    for (auto numberOfQubits = 1; numberOfQubits < 9; numberOfQubits++)
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