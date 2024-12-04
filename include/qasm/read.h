#pragma once
#include <string>
#include <vector>
#include <fstream>

struct statementString {
    std::string content;
    char delimiter;
};

std::ifstream openFile(const std::string& filePath);

std::vector<struct statementString> getStatementStrings(std::istream& stream);