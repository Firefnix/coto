#pragma once
#include <stdexcept>

class ParsingError : public std::runtime_error
{
public:
    ParsingError(const std::string &message);
};

class FileError : public ParsingError
{
public:
    FileError(const std::string &message);
};

class SyntaxError : public ParsingError
{
public:
    SyntaxError(const std::string &message);
};

class UnsupportedError : public ParsingError
{
public:
    UnsupportedError(const std::string &message);
};

class VersionError : public ParsingError
{
public:
    VersionError(const std::string &message);
};

class VariableError : public ParsingError
{
public:
    VariableError(const std::string &message);
};

class SizeError : public ParsingError
{
public:
    SizeError(const std::string &message);
};