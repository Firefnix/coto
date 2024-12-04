#pragma once
#include <string>

typedef std::string varname;

typedef bool bit;

template <class T>
struct var {
    varname name;
    bool isConst;
    bool isAssignedTo;
    T value;
};

bool varExists(const varname &name);

void defineVar(const std::string& typeName, const varname& name, bool isConst = false);

template <typename T>
void setVar(const varname &name, const T &value);
