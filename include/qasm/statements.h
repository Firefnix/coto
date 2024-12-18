/**
 * @file statements.h
 * @brief Parsing statements from QASM strings
 */
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <qasm/read.h>
#include <qasm/error.h>

class Statement {
public:
    static std::unique_ptr<Statement> parse(const struct statementString &content);
    virtual ~Statement() = default;
    virtual void execute() const = 0;
};

std::vector<std::unique_ptr<Statement>> getStatements(std::istream& stream);

std::vector<std::unique_ptr<Statement>> getStatements(const std::string& content);
