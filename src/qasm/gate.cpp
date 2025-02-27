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
        if (gateName.starts_with("p(2pi/"))
        {
            return std::stoi(gateName.substr(6, gateName.length() - 7));
        }
        return 2 * std::stoi(gateName.substr(5, gateName.length() - 6));
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

static std::string getPhaseGateName(int phase)
{
    if (phase == 1)
        return "p(0)";
    if (phase == 2)
        return "p(pi)";
    if (phase % 2 == 0)
        return "p(pi/" + std::to_string(phase / 2) + ")";
    return "p(2pi/" + std::to_string(phase) + ")";
}

bool PhaseGate::is(const std::string &gateName)
{
    if (gateName == "p(0)" || gateName == "p(pi)" || gateName == "p(2pi)")
        return true;
    if (gateName.starts_with("p(2pi/"))
    {
        if (gateName.length() < 7 || gateName[gateName.length() - 1] != ')')
            return false;
        auto base = gateName[5] == '-' ? 7 : 6;
        return std::all_of(gateName.begin() + base, gateName.end() - 1, [](char c)
                           { return std::isdigit(static_cast<unsigned char>(c)); });
    }
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
    : Gate(getPhaseGateName(phase), 1), phase(phase)
{
}

bool Gate::exists(const std::string &gateName)
{
    return isReservedName(gateName) || PhaseGate::is(gateName);
}

const Gate Gate::byName(const std::string &gateName)
{
    if (PhaseGate::is(gateName))
    {
        return PhaseGate(gateName);
    }
    else if (gateName == "x" || gateName == "h")
    {
        return Gate(gateName, 1);
    }
    else if (gateName == "s" || gateName == "cx")
    {
        return Gate(gateName, 2);
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
        return Gate::byName(name).toString();
    }
    throw VariableError("Undefined gate: " + name);
}

std::size_t Gate::size() const noexcept
{
    return gateSize;
}