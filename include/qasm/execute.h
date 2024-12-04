
#pragma once
#include <qasm/statements.h>

void execute(const std::string& content);

void execute(std::istream& stream);

void execute(const std::vector<std::unique_ptr<Statement>>& statements);
