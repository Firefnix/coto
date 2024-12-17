#include <numeric>
#include <qasm/read.h>
#include <qasm/error.h>
#include <istream>
#include <fstream>
#include <iostream>

std::vector<statementString> statementsStrings(const std::vector<std::string>& lines);
std::string beforeInLineComment(std::string line);
std::string beforeBlockComment(std::string line);
std::string afterBlockComment(std::string line);
std::vector<std::string> readFileLinesWithoutComments(std::istream& stream);

std::vector<statementString> getStatementStrings(std::istream& stream)
{
    auto lines = readFileLinesWithoutComments(stream);
    return statementsStrings(lines);
}

std::ifstream openFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw FileError("Cannot open file");
    }

    return file;
}

std::vector<std::string> readFileLinesWithoutComments(std::istream& stream)
{
    std::vector<std::string> lines;

    bool isInBlockComment = false;
    for (std::string line; std::getline(stream, line);) {
        std::string cache;
        cache.reserve(line.size());
        if (!isInBlockComment && line.find("/*") != std::string::npos) {
            isInBlockComment = true;
            cache = beforeBlockComment(line);
            if (cache != "") lines.push_back(cache);
        }
        if (isInBlockComment && line.find("*/") != std::string::npos) {
            isInBlockComment = false;
            cache = afterBlockComment(line);
            if (cache != "") lines.push_back(cache);
        } else if (!isInBlockComment) {
            cache = beforeInLineComment(line);
            if (cache != "") lines.push_back(cache);
        }
    }
    return lines;
}

std::vector<statementString> statementsStrings(const std::vector<std::string>& lines)
{
    std::string content = std::accumulate(lines.begin(), lines.end(), std::string());
    std::vector<statementString> statements;
    std::vector<char> delimiters;
    std::string current;

    for (char c : content) {
        if (c == ';' || c == '{' || c == '}') {
            statements.push_back({current, c});
            current = "";
        } else {
            current += c;
        }
    }

    return statements;
}

std::string beforeInLineComment(std::string line)
{
    return line.substr(0, line.find("//"));
}

std::string beforeBlockComment(std::string line)
{
    return line.substr(0, line.find("/*"));
}

std::string afterBlockComment(std::string line)
{
    if (line.find("*/") + 2 >= line.size()) {
        return "";
    }
    return line.substr(line.find("*/") + 2);
}

bool isOnlyEmptyCharacters(const std::string& str)
{
    return str.find_first_not_of(" \t\n\v\f\r;") == std::string::npos;
}