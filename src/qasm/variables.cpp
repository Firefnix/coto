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
