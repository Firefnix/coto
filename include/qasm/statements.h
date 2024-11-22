#pragma once
#include <string>
#include <vector>
#include <qasm/read.h>

class Statement {
public:
    static Statement parse(const struct statementString &content);
    void execute();
};

std::vector<Statement> getStatements(std::istream& stream);

std::vector<Statement> getStatements(const std::string& content);
