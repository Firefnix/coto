/**
 * @file qasm.h
 * @brief General header for the QASM library
 */
#pragma once
#include <istream>

namespace qasm
{
    void exec(const std::string& content);

    void exec(std::istream& stream);

    void fexec(const std::string& filePath);

    std::string eval(const std::string& identifier);
}
