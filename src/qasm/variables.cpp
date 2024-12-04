#include <vector>
#include <qasm/error.h>
#include <qasm/variables.h>

std::vector<var<int>> intVars;
std::vector<var<bit>> bitVars;

enum vartype {IntVar, BitVar, NotDefined};

vartype varType(const varname& name)
{
    for (auto v : intVars) {
        if (v.name == name) return IntVar;
    }
    for (auto v : bitVars) {
        if (v.name == name) return BitVar;
    }
    return NotDefined;
}


bool varExists(const varname &name)
{
    return varType(name) != NotDefined;
}

void defineVar(const std::string& typeName, const varname &name, bool isConst)
{
    if (typeName == "int") {
        intVars.push_back(var<int>{name, isConst, false});
    } else if (typeName == "bit") {
        bitVars.push_back(var<bit>{name, isConst, false});
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
        default:
            throw VariableError("Trying to assign undefined variable" + name);
    }
}
