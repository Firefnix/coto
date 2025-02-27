#include <gtest/gtest.h>
#include <gateappliers.h>

const size_t MAX_QUBITS = 8;

size_t flipNthBit(const size_t n, const size_t index)
{
    return index ^ (1 << n);
}

TEST(GateAppliersTest, X)
{
    for (auto numberOfQubits = 1; numberOfQubits < MAX_QUBITS; numberOfQubits++)
    {
        for (auto qubitToApplyXOn = 0; qubitToApplyXOn < numberOfQubits; qubitToApplyXOn++)
        {
            ampl::ConcreteState base(numberOfQubits);
            for (auto i = 0; i < base.size(); i++)
            {
                base[i] = i;
            }
            Evaluation result(numberOfQubits);
            for (auto i = 0; i < result.size(); i++)
            {
                result[flipNthBit(numberOfQubits - qubitToApplyXOn - 1, i)] = i;
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

TEST(GateAppliersTest, phase)
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
                                  ? absi::Interval(i)
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

TEST(GateAppliersTest, gateMatrixIdentity)
{
    for (auto numberOfQubits = 1; numberOfQubits < MAX_QUBITS; numberOfQubits++)
    {
        for (auto qubitToApplyIdentityOn = 0; qubitToApplyIdentityOn < numberOfQubits; qubitToApplyIdentityOn++)
        {
            gateappliers::GateMatrix id(1);
            id(0, 0) = 1;
            id(1, 1) = 1;

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
                EXPECT_EQ(ev[i], base[i])
                    << "Failed appplying identity on qubit 0"
                    << " at index " << i
                    << " got " << ev[i].to_string()
                    << ", expected " << base[i];
            }
        }
    }
}

TEST(GateAppliersTest, gateMatrixHadamardOnQubit0)
{
    absi::Interval coefficients[] = {1, 1, 1, -1};
    gateappliers::GateMatrix gate(1, coefficients);

    ampl::Amplitude v[] = {1, 2, 3, 4};
    ampl::ConcreteState base(2, v);

    auto d = Diagram::fromStateVector(base);

    gateappliers::applyGateMatrix(d, 0, gate);

    auto ev = d->evaluate();
    EXPECT_EQ(ev[0], 4) << ev[0].to_string() << " != 4";
    EXPECT_EQ(ev[1], 6) << ev[1].to_string() << " != 6";
    EXPECT_EQ(ev[2], -2) << ev[2].to_string() << " != -2";
    EXPECT_EQ(ev[3], -2) << ev[3].to_string() << " != -2";
}

TEST(GateAppliersTest, gateMatrixHadamardOnQubit1)
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
        EXPECT_EQ(computed[i], expected[i])
            << "Failed applying H on qubit 1 at index " << i
            << ", computed " << computed[i].to_string()
            << ", expected " << expected[i];
    }
}

TEST(GateAppliersTest, applyHConsistency)
{
    auto h = gateappliers::GateMatrix(1);
    h(0, 0) = ampl::invSqrt2;
    h(0, 1) = ampl::invSqrt2;
    h(1, 0) = ampl::invSqrt2;
    h(1, 1) = -ampl::invSqrt2;

    const auto numberOfQubits = 4;
    for (auto q = 0; q < numberOfQubits; q++)
    {
        auto d0 = Diagram::random(numberOfQubits);
        auto d1 = d0.clone();
        gateappliers::applyGateMatrix(&d0, q, h);
        gateappliers::applyH(d1, q);

        auto e0 = d0.evaluate();
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

TEST(GateAppliersTest, applyS)
{
    ampl::Amplitude v[] = {1, 2, 3, 4};
    ampl::ConcreteState base(2, v);

    auto d = Diagram::fromStateVector(base);

    gateappliers::applyS(d, 0, 1);

    auto ev = d->evaluate();
    EXPECT_EQ(ev[0], 1) << ev[0].to_string() << " != 1";
    EXPECT_EQ(ev[1], 3) << ev[1].to_string() << " != 3";
    EXPECT_EQ(ev[2], 2) << ev[2].to_string() << " != 2";
    EXPECT_EQ(ev[3], 4) << ev[3].to_string() << " != 4";
}

TEST(GateAppliersTest, applyCX)
{
    ampl::Amplitude v[] = {1, 2, 3, 4};
    ampl::ConcreteState base(2, v);

    auto d = Diagram::fromStateVector(base);

    gateappliers::applyCX(d, 0, 1);

    auto ev = d->evaluate();
    EXPECT_EQ(ev[0], 1) << ev[0].to_string() << " != 1";
    EXPECT_EQ(ev[1], 2) << ev[1].to_string() << " != 2";
    EXPECT_EQ(ev[2], 4) << ev[2].to_string() << " != 4";
    EXPECT_EQ(ev[3], 3) << ev[3].to_string() << " != 3";
}

TEST(GateAppliersTest, applyCXOnQubit1and2)
{
    ampl::Amplitude v[] = {1, 2, 3, 4, 5, 6, 7, 8};
    ampl::ConcreteState base(3, v);

    auto d = Diagram::fromStateVector(base);

    gateappliers::applyCX(d, 1, 2);

    auto ev = d->evaluate();
    ampl::Amplitude expected[] = {1, 2, 4, 3, 5, 6, 8, 7};
    for (auto i = 0; i < 8; i++)
    {
        EXPECT_EQ(ev[i], expected[i])
            << "Failed applying CX on qubit 1 and 2 at index " << i
            << ", got " << ev[i].to_string()
            << ", expected " << expected[i];
    }
}

TEST(GateAppliersTest, applyH)
{
    const ampl::Amplitude v[] = {1, 0, 0, 0};
    const ampl::Amplitude afterH[] = {ampl::invSqrt2, 0, ampl::invSqrt2, 0};
    const ampl::ConcreteState base(2, v);
    auto d = Diagram::fromStateVector(base);

    gateappliers::applyH(d, 0);
    auto ev = d->evaluate();
    for (auto i = 0; i < ev.size(); i++)
    {
        EXPECT_EQ(ev[i], afterH[i])
            << "Failed applying H in debug (after H) at index " << i
            << ", got " << ev[i].to_string()
            << ", expected " << afterH[i];
    }
}

/*
TEST_F(GateAppliersTest, debug)
{
    const ampl::Amplitude v[] = {1, 0, 0, 0};
    const ampl::Amplitude afterH[] = {ampl::invSqrt2, 0, ampl::invSqrt2, 0};
    const Interval expected[] = {ampl::invSqrt2, 0, 0, ampl::invSqrt2};
    const ampl::ConcreteState base(2, v);
    std::cout << "- - - - - Creating d - - - - -" << std::endl;
    auto d = Diagram::fromStateVector(base);
    std::cout << "- - - - - Creating d2 - - - - -" << std::endl;
    auto d2 = Diagram::fromStateVector(ampl::ConcreteState(2, afterH));

    std::cout << "- - - - - Applying H - - - - -" << std::endl;
    gateappliers::applyH(d, 0);
    auto ev = d->evaluate();
    auto ev2 = d2->evaluate();

    for (auto i = 0; i < base.size(); i++)
    {
        EXPECT_EQ(ev[i], ev2[i])
            << "Failed applying H in debug (after H) at index " << i
            << ", got " << ev[i].to_string()
            << ", expected " << ev2[i].to_string();
    }

    std::cout << "- - - - - Applying CX on d - - - - -" << std::endl;
    // reduction::cutDeadBranches(d);
    gateappliers::applyCX(d, 0, 1);
    // reduction::cutDeadBranches(d);
    std::cout << "- - - - - Applying CX on d2 - - - - -" << std::endl;

    gateappliers::applyCX(d2, 0, 1);
    auto evcx = d->evaluate();
    auto evcx2 = d2->evaluate();

    for (auto i = 0; i < base.size(); i++)
    {
        EXPECT_EQ(evcx2[i], expected[i])
            << "Failed applying H and CX in debug at index " << i
            << ", got " << evcx2[i].to_string()
            << ", expected " << expected[i].to_string();
    }

    for (auto i = 0; i < base.size(); i++)
    {
        EXPECT_EQ(evcx[i], expected[i])
            << "Failed applying H and CX in debug at index " << i
            << ", got " << evcx[i].to_string()
            << ", expected " << expected[i].to_string();
    }
}
// */