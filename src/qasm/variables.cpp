#include <vector>
#include <qasm/error.h>
#include <qasm/variables.h>

std::vector<var<int>> intVars;
std::vector<var<bit>> bitVars;

bool varExists(const varname &name)
{
    for (auto v : intVars) {
        if (v.name == name) return true;
    }
    for (auto v : bitVars) {
        if (v.name == name) return true;
    }
    return false;
}


template <typename T>
var<T> getVar(const varname& name)
{
    for (var<T> v : getVarStorage<T>()) {
        if (v.name == name) {
            return v;
        }
    }
    throw VariableError("Variable not found");
}

template<typename T>
void setVar(const varname& name, const T& value)
{
    for (var<T>& v : getVarStorage<T>())
    {
        if (v.name == name) {
            if (v.isConst) {
                throw VariableError("Trying to reassign a const variable.");
            }
            v.value = value;
            v.isAssignedTo = true;
        }
    }
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
