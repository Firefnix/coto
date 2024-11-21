#include <qasm/error.h>

ParsingError::ParsingError(const std::string &message)
    : std::runtime_error(message)
{
}

FileError::FileError(const std::string &message) : ParsingError(message)
{
}

SyntaxError::SyntaxError(const std::string &message) : ParsingError(message)
{
}

UnsupportedError::UnsupportedError(const std::string &message) : ParsingError(message)
{
}

VersionError::VersionError(const std::string &message) : ParsingError(message)
{
}

VariableError::VariableError(const std::string &message) : ParsingError(message)
{
}

SizeError::SizeError(const std::string &message) : ParsingError(message)
{
}
