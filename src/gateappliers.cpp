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
    static const absi::Interval hCoefficients[] = {
        ampl::invSqrt2, ampl::invSqrt2,
        ampl::invSqrt2, -ampl::invSqrt2};
    static const gateappliers::GateMatrix hGate(1, hCoefficients);
    assertQubitIsValid(d, q);
    applyGateMatrix(d, q, hGate);
}

void gateappliers::applyS(Diagram *d, qubit a, qubit b)
{
    static const absi::Interval sCoefficients[] = {
        1, 0, 0, 0,
        0, 0, 1, 0,
        0, 1, 0, 0,
        0, 0, 0, 1};
    static const gateappliers::GateMatrix sGate(2, sCoefficients);
    assertQubitIsValid(d, a);
    assertQubitIsValid(d, b);

    if (b != a + 1)
    {
        throw std::runtime_error("Gate applying on non-contiguous qubit is not implemented yet");
    }
    applyGateMatrix(d, a, sGate);
}

void gateappliers::applyCX(Diagram *d, qubit a, qubit b)
{
    static const absi::Interval cxCoefficients[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 0, 1,
        0, 0, 1, 0};
    static const gateappliers::GateMatrix cxGate(2, cxCoefficients);
    assertQubitIsValid(d, a);
    assertQubitIsValid(d, b);
    if (b != a + 1)
    {
        throw std::runtime_error("Gate applying on non-contiguous qubits is not implemented yet");
    }
    applyGateMatrix(d, a, cxGate);
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

static branches cloneBranches(const branches &brs)
{
    branches cloned;
    for (const auto &g : brs)
    {
        cloned.push_back({.x = g.x, .d = g.d->clone()});
    }
    return cloned;
}

static void applyGateOnFirstQubits(Diagram *diagram, const gateappliers::GateMatrix &matrix)
{
    if (matrix.height() == 1)
    {
        apply1QubitGateOnQubit0(diagram, matrix);
        return;
    }

    auto m00 = matrix.topLeft();
    auto m01 = matrix.topRight();
    auto m10 = matrix.bottomLeft();
    auto m11 = matrix.bottomRight();
    auto clonedLeft = cloneBranches(diagram->left);
    for (auto &g : diagram->left)
    {
        applyGateOnFirstQubits(g.d, m00);
    }
    for (auto &d : diagram->right)
    {
        auto clone = d.d->clone();
        applyGateOnFirstQubits(clone, m01);
        diagram->lefto(clone, d.x);

        applyGateOnFirstQubits(d.d, m11);
    }
    for (auto &g : clonedLeft)
    {
        auto clone = g.d->clone();
        applyGateOnFirstQubits(clone, m10);
        diagram->righto(clone, g.x);
    }
}

void gateappliers::applyGateMatrix(Diagram *diagram, qubit q, const GateMatrix &matrix)
{
    assertQubitIsValid(diagram, q);
    const auto k = diagram->height - q; // 0 <= k < d->height

    if (q == 0)
    {
        applyGateOnFirstQubits(diagram, matrix);
        return;
    }
    for (auto &g : diagram->getNodePointersAtHeight(k))
    {
        applyGateOnFirstQubits(g, matrix);
    }
}
