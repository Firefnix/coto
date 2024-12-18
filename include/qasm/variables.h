#pragma once
#include <string>
#include <set>

typedef std::string varname;

typedef bool bit;

typedef unsigned qubit;

/**
 * @brief A template structure representing a variable.
 *
 * @tparam T The type of the variable's value.
 */
template <class T>
struct var {
    varname typeName;      /**< The name of the variable's type. */
    varname name;          /**< The name of the variable. */
    bool isConst;          /**< Indicates if the variable is constant. */
    bool isAssignedTo;     /**< Indicates if the variable has been assigned a value. */
    T value;               /**< The value of the variable. */
};

bool isReservedName(const varname& name) noexcept;

std::string varToString(const varname& name);

void defineVar(const std::string& typeName, const varname& name, bool isConst = false);

void assignVar(const varname& name, const std::string& value);

qubit getQubit(const varname& name);
