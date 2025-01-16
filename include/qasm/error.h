/**
 * @file error.h
 * @brief Internal errors of the QASM parser
 */

#pragma once
#include <stdexcept>

/// @brief Exception thrown when a parsing error occurs
class ParsingError : public std::runtime_error
{
public:
    ParsingError(const std::string &message);
};

/// @brief Exception thrown when a file error occurs
class FileError : public ParsingError
{
public:
    FileError(const std::string &message);
};

/// @brief Exception thrown when an incorrect syntax is used
class SyntaxError : public ParsingError
{
public:
    SyntaxError(const std::string &message);
};

/// @brief Exception thrown when trying to use an unsupportedOpenQASM version
class VersionError : public ParsingError
{
public:
    VersionError(const std::string &message);
};

/// @brief Exception thrown when a variable error occurs (e.g. not found)
class VariableError : public ParsingError
{
public:
    VariableError(const std::string &message);
};

/// @brief Exception thrown when trying to apply a gate to an incorrect number of qubits
class SizeError : public ParsingError
{
public:
    SizeError(const std::string &message);
};