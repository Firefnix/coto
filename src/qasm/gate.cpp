#include <qasm/gate.h>
#include <qasm/error.h>
#include <qasm/context.h>

Gate::Gate(const std::string &name, const std::size_t size)
    : gateSize(size), name(name)
{
}

std::string Gate::toString() const noexcept
{
    return "gate: " + name + "[" + std::to_string(size()) + "]";
}

bool Gate::exists(const std::string &gateName)
{
    return isReservedName(gateName);
}

const Gate *Gate::byName(const std::string &gateName)
{
    static const Gate X = Gate("X", 1);
    static const Gate H = Gate("H", 1);
    static const Gate CX = Gate("CX", 2);
    static const Gate S = Gate("S", 2);
    if (gateName == "X")
    {
        return &X;
    }
    else if (gateName == "H")
    {
        return &H;
    }
    else if (gateName == "CX")
    {
        return &CX;
    }
    else if (gateName == "S")
    {
        return &S;
    }
    throw VariableError("Undefined gate " + gateName);
}

void Gate::applyTo(const std::vector<varname> &qubitsNames) const
{
    std::vector<qubit> qubits;
    for (auto name : qubitsNames)
    {
        qubits.push_back(getQubit(name));
    }
    applyTo(qubits);
}

void Gate::applyTo(const std::vector<qubit> &qubits) const
{
    if (size() != qubits.size())
    {
        throw SizeError("Trying to apply a gate of size " + std::to_string(size()) + " to " + std::to_string(qubits.size()) + " qubits");
    }
    applyGate(this, qubits);
}

std::string gateToString(const std::string &name)
{
    if (isReservedName(name))
    {
        return Gate::byName(name)->toString();
    }
    throw VariableError("Undefined gate: " + name);
}

std::size_t Gate::size() const noexcept
{
    return gateSize;
}