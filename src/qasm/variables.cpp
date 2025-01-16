#include <qasm/error.h>
#include <qasm/variables.h>

#include <vector>
#include <set>
#include <algorithm>

static std::vector<var<int>> intVars;
static std::vector<var<bit>> bitVars;
static std::vector<var<qubit>> qubitVars;

enum vartype
{
    IntVar,
    BitVar,
    QubitVar,
    NotDefined
};

vartype varType(const varname &name)
{
    for (const auto &v : intVars)
    {
        if (v.name == name)
            return IntVar;
    }
    for (const auto &v : bitVars)
    {
        if (v.name == name)
            return BitVar;
    }
    for (const auto &v : qubitVars)
    {
        if (v.name == name)
            return QubitVar;
    }
    return NotDefined;
}

template <typename T>
std::string to_string(const var<T> variable)
{
    return variable.typeName + ": " + std::to_string(variable.value);
}

std::string varToString(const varname &name)
{
    for (const auto &v : intVars)
    {
        if (v.name == name)
            return to_string(v);
    }
    for (const auto &v : bitVars)
    {
        if (v.name == name)
            return to_string(v);
    }
    for (const auto &v : qubitVars)
    {
        if (v.name == name)
            return to_string(v);
    }
    throw VariableError("No such variable: " + name);
}

qubit newQubit()
{
    static unsigned counter = 0;
    counter++;
    return counter - 1;
}

bool isReservedName(const varname &name) noexcept
{
    static const std::set<std::string> reservedNames{"X", "H", "CX", "S"};
    return reservedNames.contains(name);
}

void defineVar(const std::string &typeName, const varname &name, bool isConst)
{
    if (isReservedName(name))
    {
        throw VariableError("Trying to define a variable with a reserved name: " + name);
    }
    if (typeName == "int")
    {
        intVars.push_back(var<int>{typeName, name, isConst, false});
    }
    else if (typeName == "bit")
    {
        bitVars.push_back(var<bit>{typeName, name, isConst, false});
    }
    else if (typeName == "qubit")
    {
        qubitVars.push_back(var<qubit>{typeName, name, true, true, newQubit()});
    }
    else
    {
        throw VariableError("Unsupported variable type in definition: '" + typeName + "'");
    }
}

template <typename T>
void setValue(const varname &name, std::vector<var<T>> *vars, const T &value)
{
    for (auto &v : *vars)
    {
        if (v.name == name)
        {
            if (v.isConst)
            {
                throw VariableError("Trying to assign to const variable " + name);
            }
            v.value = value;
            return;
        }
    }
}

void assignVar(const varname &name, const std::string &value)
{
    switch (varType(name))
    {
    case IntVar:
        setValue(name, &intVars, std::stoi(value));
        break;
    case BitVar:
        setValue(name, &bitVars, std::stoi(value) != 0);
        break;
    case QubitVar:
        throw VariableError("Trying to assign to qubit " + name);
    default:
        throw VariableError("Trying to assign undefined variable" + name);
    }
}

qubit getQubit(const varname &name)
{
    for (auto v : qubitVars)
    {
        if (v.name == name)
        {
            return v.value;
        }
    }
    throw VariableError("Qubit not defined: " + name);
}