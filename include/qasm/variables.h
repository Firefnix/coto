#pragma once
#include <string>
#include <set>

typedef std::string varname;

typedef bool bit;

typedef unsigned qubit;

template <class T>
struct var {
    varname typeName;
    varname name;
    bool isConst;
    bool isAssignedTo;
    T value;
};

bool isReservedName(const varname& name);

bool varExists(const varname &name);

std::string varToString(const varname& name);

void defineVar(const std::string& typeName, const varname& name, bool isConst = false);

void assignVar(const varname& name, const std::string& value);

qubit getQubit(const varname& name);
