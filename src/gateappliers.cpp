#include <gateappliers.h>


void gateappliers::applyX(Diagram *d, qubit q)
{
    if (d->height < q)
    {
        throw std::runtime_error("Invalid qubit");
    }
    throw std::runtime_error("Not implemented");
}

void gateappliers::applyH(Diagram *d, qubit q)
{
    if (d->height < q)
    {
        throw std::runtime_error("Invalid qubit");
    }
    throw std::runtime_error("Not implemented");
}

void gateappliers::applyS(Diagram *d, qubit a, qubit b)
{
    if (d->height < a || d->height < b)
    {
        throw std::runtime_error("Invalid qubit");
    }
    throw std::runtime_error("Not implemented");
}

void gateappliers::applyCX(Diagram *d, qubit a, qubit b)
{
    if (d->height < a || d->height < b)
    {
        throw std::runtime_error("Invalid qubit");
    }
    throw std::runtime_error("Not implemented");
}