#include <qasm/error.h>

ParsingError::ParsingError(const string &message)
    : std::runtime_error(message)
{
}

FileError::FileError(const string &message) : ParsingError(message)
{
}

SyntaxError::SyntaxError(const string &message) : ParsingError(message)
{
}

VersionError::VersionError(const string &message) : ParsingError(message)
{
}

VariableError::VariableError(const string &message) : ParsingError(message)
{
}

SizeError::SizeError(const string &message) : ParsingError(message)
{
}
