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
    assertQubitIsValid(d, q);
    throw std::runtime_error("Not implemented");
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