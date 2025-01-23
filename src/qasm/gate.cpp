#include <qasm/gate.h>
#include <qasm/error.h>
#include <qasm/context.h>

#include <algorithm>

Gate::Gate(const std::string &name, const std::size_t size)
    : gateSize(size), name(name)
{
}

std::string Gate::toString() const noexcept
{
    return "gate: " + name + "[" + std::to_string(size()) + "]";
}

static int getPhaseGatePhase(const std::string &gateName)
{
    try
    {
        return std::stoi(gateName.substr(5, gateName.length() - 6));
    }
    catch (std::invalid_argument &e)
    {
        throw VariableError("Phase gate phase is not a number");
    }
    catch (std::out_of_range &e)
    {
        throw VariableError("Phase gate phase out of range");
    }
}

bool PhaseGate::is(const std::string &gateName)
{
    if (!gateName.starts_with("p(pi/") || gateName.length() < 6 || gateName[gateName.length() - 1] != ')')
        return false;
    auto base = gateName[5] == '-' ? 6 : 5;
    return std::all_of(gateName.begin() + base, gateName.end() - 1, [](char c)
                       { return std::isdigit(static_cast<unsigned char>(c)); });
}

PhaseGate::PhaseGate(const std::string &gateName)
    : PhaseGate(getPhaseGatePhase(gateName))
{
}

PhaseGate::PhaseGate(int phase)
    : Gate("p(pi/" + std::to_string(phase) + ")", 1), phase(phase)
{
}

bool Gate::exists(const std::string &gateName)
{
    return isReservedName(gateName) || PhaseGate::is(gateName);
}

const Gate *Gate::byName(const std::string &gateName)
{
    static const Gate X = Gate("x", 1);
    static const Gate H = Gate("h", 1);
    static const Gate CX = Gate("cx", 2);
    static const Gate S = Gate("s", 2);
    if (PhaseGate::is(gateName))
    {
        return new PhaseGate(gateName);
    }
    else if (gateName == X.name)
    {
        return &X;
    }
    else if (gateName == H.name)
    {
        return &H;
    }
    else if (gateName == CX.name)
    {
        return &CX;
    }
    else if (gateName == S.name)
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
    if (Gate::exists(name))
    {
        return Gate::byName(name)->toString();
    }
    throw VariableError("Undefined gate: " + name);
}

std::size_t Gate::size() const noexcept
{
    return gateSize;
}