#include <gateappliers.h>

static void assertQubitIsValid(Diagram *d, qubit q)
{
    if (d->height < q)
    {
        throw std::runtime_error("Invalid qubit: Trying to apply qubit " + std::to_string(q) + " to a diagram of height " + std::to_string(d->height));
    }
}

void gateappliers::applyX(Diagram *d, qubit q)
{
    assertQubitIsValid(d, q);
    if (q == 0)
    {
        std::swap(d->left, d->right);
        return;
    }
    for (auto &g : d->left)
    {
        applyX(g.d, q - 1);
    }
    for (auto &g : d->right)
    {
        applyX(g.d, q - 1);
    }
}

void gateappliers::applyH(Diagram *d, qubit q)
{
    static gateappliers::GateMatrix hadamardGate(1);
    static bool didInit = false;
    assertQubitIsValid(d, q);
    if (!didInit)
    {
        hadamardGate(0, 0) = absi::Interval::singleton(ampl::invSqrt2);
        hadamardGate(0, 1) = absi::Interval::singleton(ampl::invSqrt2);
        hadamardGate(1, 0) = absi::Interval::singleton(ampl::invSqrt2);
        hadamardGate(1, 1) = absi::Interval::singleton(-ampl::invSqrt2);
        didInit = true;
    }
    applyGateMatrix(d, q, hadamardGate);
}

void gateappliers::applyS(Diagram *d, qubit a, qubit b)
{
    assertQubitIsValid(d, a);
    assertQubitIsValid(d, b);
    throw std::runtime_error("Not implemented");
}

void gateappliers::applyCX(Diagram *d, qubit a, qubit b)
{
    assertQubitIsValid(d, a);
    assertQubitIsValid(d, b);
    throw std::runtime_error("Not implemented");
}

void gateappliers::applyPhase(Diagram *d, qubit q, int phaseDenominator)
{
    assertQubitIsValid(d, q);
    const auto phaseShift = absi::Interval::exp2iPiOver(phaseDenominator);
    for (auto &d : d->getNodePointersAtHeight(d->height - q))
    {
        for (auto &g : d->right)
        {
            g.x = phaseShift * g.x;
        }
    }
}

static void apply1QubitGateOnQubit0(Diagram *diagram, const gateappliers::GateMatrix &matrix)
{
    if (matrix.height() != 1)
    {
        throw std::runtime_error("Invalid matrix height: " + std::to_string(matrix.height()));
    }
    auto m00 = matrix.topLeft().value();
    auto m01 = matrix.topRight().value();
    auto m10 = matrix.bottomLeft().value();
    auto m11 = matrix.bottomRight().value();
    auto baseLeft = diagram->left;
    for (auto &g : diagram->left)
    {
        g.x = m00 * g.x; // No need to clone
    }
    for (auto &d : diagram->right)
    {
        diagram->lefto(d.d, m01 * d.x);
        d.x = m11 * d.x; // No need to clone
    }
    for (auto &g : baseLeft)
    {
        diagram->righto(g.d, m10 * g.x);
    }
}

void gateappliers::applyGateMatrix(Diagram *d, qubit q, const GateMatrix &m)
{
    assertQubitIsValid(d, q);
    const auto k = d->height - q; // 0 <= k < d->height

    if (m.height() == 1)
    {
        for (auto &g : d->getNodePointersAtHeight(k))
        {
            apply1QubitGateOnQubit0(g, m);
        }
        return;
    }
    throw std::runtime_error("Not implemented");

    for (auto &baseNode : d->getNodePointersAtHeight(k))
    {
        auto d00 = baseNode; // No need to clone
        auto d01 = baseNode->clone();
        auto d10 = baseNode->clone();
        auto d11 = baseNode->clone();
        for (const auto &g : d->left)
        {
            g.d->righto(d01, g.x);
        }
        for (auto &r : d->right)
        {
            r.d->lefto(d10, r.x);
            r.d = d11;
        }
        applyGateMatrix(d00, q - 1, m.topLeft());
        applyGateMatrix(d01, q - 1, m.topRight());
        applyGateMatrix(d10, q - 1, m.bottomLeft());
        applyGateMatrix(d11, q - 1, m.bottomRight());
    }
}
