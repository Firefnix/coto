#include <vector>
#include <qasm/error.h>
#include <qasm/variables.h>

std::vector<var<int>> intVars;
std::vector<var<bit>> bitVars;
std::vector<var<qubit>> qubitVars;

enum vartype {IntVar, BitVar, QubitVar, NotDefined};

vartype varType(const varname& name)
{
    for (const auto& v : intVars) {
        if (v.name == name) return IntVar;
    }
    for (const auto& v : bitVars) {
        if (v.name == name) return BitVar;
    }
    for (const auto& v : qubitVars) {
        if (v.name == name) return QubitVar;
    }
    return NotDefined;
}

bool varExists(const varname &name)
{
    return varType(name) != NotDefined;
}

qubit newQubit()
{
    static unsigned counter = 0;
    counter++;
    return counter-1;
}

void defineVar(const std::string& typeName, const varname &name, bool isConst)
{
    if (typeName == "int") {
        intVars.push_back(var<int>{name, isConst, false});
    } else if (typeName == "bit") {
        bitVars.push_back(var<bit>{name, isConst, false});
    } else if (typeName == "qubit") {
        qubitVars.push_back(var<qubit>{name, true, true, newQubit()});
    } else {
        throw VariableError("Unsupported variable type in definition: '" + typeName + "'");
    }
}

template<typename T>
void setValue(const varname& name, std::vector<var<T>> vars, const T& value)
{
    for (auto& v : vars)
    {
        if (v.name == name)
        {
            if (v.isConst) {
                throw VariableError("Trying to assign to const variable " + name);
            }
            v.value = value;
            return;
        }
    }
}

void assignVar(const varname& name, const std::string& value)
{
    switch (varType(name))
    {
        case IntVar:
            setValue(name, intVars, std::stoi(value));
            break;
        case BitVar:
            setValue(name, bitVars, std::stoi(value) != 0);
            break;
        case QubitVar:
            throw VariableError("Trying to assign to qubit " + name);
        default:
            throw VariableError("Trying to assign undefined variable" + name);
    }
}
