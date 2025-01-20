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
