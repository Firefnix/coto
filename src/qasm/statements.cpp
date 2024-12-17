#include <iostream>
#include <algorithm>
#include <optional>
#include <sstream>

#include <qasm/statements.h>
#include <qasm/variables.h>
#include <qasm/gate.h>

bool isValidIdentifier(std::string identifier)
{
    bool isFirstChar = true;
    for (char c : identifier) {
        if (c < 'A' || c > 'z') {
            if (c == '_') {
                continue;
            }
            if (!isFirstChar && c > '0' && c < '9') {
                continue;
            }
            return false;
        }
        isFirstChar = false;
    }
    return true;
}

class DefinitionStatement : public Statement {
public:
    static bool is(const std::string &content)
    {
        return std::ranges::count(content, ' ') == 1;
    }

    DefinitionStatement(std::string content)
        : typeName(content.substr(0, content.find(' '))),
          name(content.substr(content.find(' ') + 1))
    {
        if (!isValidIdentifier(typeName)) {
            throw SyntaxError("Invalid type name identifier in definition statement");
        }
        if (!isValidIdentifier(name)) {
            throw SyntaxError("Invalid name identifier in definition statement");
        }
    }

    void execute() const override
    {
        defineVar(typeName, name, false);
    }

    const std::string typeName;
    const std::string name;
};

class AssignmentStatement : public Statement {
public:
    static bool is(const std::string &content)
    {
        return std::ranges::count(content, '=') == 1;
    }

    AssignmentStatement(const std::string &content)
    {
        auto eqPos = content.find('=');
        auto beforeEqual = content.substr(0, eqPos);
        auto spacePos = beforeEqual.find(' ');
        if (spacePos != std::string::npos) {
            if (!isValidIdentifier(beforeEqual.substr(0, spacePos))) {
                throw SyntaxError("Invalid type identifier in assignment statement");
            }
            if (!isValidIdentifier(beforeEqual.substr(spacePos + 1))) {
                throw SyntaxError("Invalid identifier in assignment statement");
            }
            typeName = beforeEqual.substr(0, spacePos);
            name = beforeEqual.substr(spacePos + 1);
            value = content.substr(eqPos + 1);
            return;
        }
        if (!isValidIdentifier(beforeEqual)) {
            throw SyntaxError("Invalid identifier in assignment statement");
        }
        name = beforeEqual;
        value = content.substr(eqPos + 1);
    }

    void execute() const override
    {
        if (typeName.has_value()) {
            defineVar(typeName.value(), name);
        }
        assignVar(name, value);
    };

    std::optional<std::string> typeName;
    std::string name;
    std::string value;
};

class GateApplyStatement : public Statement {
public:
    GateApplyStatement(std::string gateName, std::vector<std::string> qubitsNames) : gateName(gateName), qubitsNames(qubitsNames) {}

    static bool is(const std::string &content)
    {
        return std::ranges::count(content, ' ') >= 1;
    }

    GateApplyStatement(const std::string &content)
    {
        auto firstSpacePos = content.find(' ');
        auto qubitsStr = content.substr(firstSpacePos + 1);
        gateName = content.substr(0, firstSpacePos);
        qubitsNames.reserve(std::ranges::count(qubitsStr, ' ') + 1);

        while (qubitsStr.size() > 0) {
            auto commaPos = qubitsStr.find(' ');
            if (commaPos == std::string::npos) {
                qubitsNames.push_back(qubitsStr);
                break;
            }
            qubitsNames.push_back(qubitsStr.substr(0, commaPos));
            qubitsStr = qubitsStr.substr(commaPos + 1);
        }
    }

    void execute() const override
    {
        auto gate = Gate::byName(gateName);
        gate->applyTo(qubitsNames);
    };

    std::string gateName;
    std::vector<std::string> qubitsNames;
};

class VersionStatement : public Statement {
public:
    VersionStatement(const std::string &content) : version(content.length() > 9 ? content.substr(9) : "")
    {
        if (version != "3" && version != "3.0") {
            throw VersionError("Unsupported version '" + version + "'");
        }
    }

    static bool is(const std::string &content)
    {
        return content.starts_with("OPENQASM ");
    }

    void execute() const override {};

    const std::string version;
};

class IncludeStatement : public Statement {
public:
    IncludeStatement(const std::string& content) :
        filePath(content.substr(9, content.size()-1)) {};

    static bool is(const std::string &content)
    {
        return content.starts_with("include \"");
    }

    void execute() const override {};

private:
    const std::string filePath;
};

class ForBeginStatement : public Statement {
public:
    ForBeginStatement(const std::string &content) : content(content) {};

    void execute() const override {};

    const std::string content;
};

class ForEndStatement : public Statement {
public:
    ForEndStatement(const std::string &content) : content(content) {};

    void execute() const override {};

    const std::string content;
};

std::unique_ptr<Statement> Statement::parse(const struct statementString &ss)
{
    if (ss.delimiter == ';') {
        if (VersionStatement::is(ss.content)) {
            return std::make_unique<VersionStatement>(ss.content);
        }
        if (IncludeStatement::is(ss.content)) {
            return std::make_unique<IncludeStatement>(ss.content);
        }
        if (AssignmentStatement::is(ss.content)) {
            return std::make_unique<AssignmentStatement>(ss.content);
        }
        if (DefinitionStatement::is(ss.content)) {
            return std::make_unique<DefinitionStatement>(ss.content);
        }
        if (GateApplyStatement::is(ss.content)) {
            return std::make_unique<GateApplyStatement>(ss.content);
        }
    } else if (ss.delimiter == '{') {
        return std::make_unique<ForBeginStatement>(ss.content);
    } else if (ss.delimiter == '}') {
        return std::make_unique<ForEndStatement>(ss.content);
    }
    throw SyntaxError("Invalid statement delimiter");
}

std::vector<std::unique_ptr<Statement>> parseStatements(const std::vector<statementString>& stmtsStrings)
{
    std::vector<std::unique_ptr<Statement>> stmts;
    for (statementString ss : stmtsStrings) {
        stmts.push_back(Statement::parse(ss));
    }
    return stmts;
}

std::vector<std::unique_ptr<Statement>> getStatements(std::istream& stream)
{
    auto stmtsStrings = getStatementStrings(stream);
    return parseStatements(stmtsStrings);
}

std::vector<std::unique_ptr<Statement>> getStatements(const std::string& content)
{
    std::istringstream stream(content);
    return getStatements(stream);
}
