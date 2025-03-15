/**
 * @file variables.h
 * @brief Handling QASM variables
 */
#pragma once
#include <string>
#include <set>

using std::string;

typedef string varname;

typedef bool bit;

typedef unsigned qubit;

/**
 * @brief A template structure representing a variable.
 *
 * @tparam T The type of the variable's value.
 */
template <class T>
struct Var
{
    varname type_name;    /**< The name of the variable's type. */
    varname name;        /**< The name of the variable. */
    bool is_const;       /**< Indicates if the variable is constant. */
    bool is_assigned_to; /**< Indicates if the variable has been assigned a value. */
    T value;             /**< The value of the variable. */
};

bool is_name_reserved(const varname &name) noexcept;

std::string var_to_string(const varname &name);

void define_var(const string &type_name, const varname &name, bool is_const = false);

void assign_var(const varname &name, const string &value);

qubit get_qubit(const varname &name);
