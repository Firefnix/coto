#include <qasm/execute.h>

void execute(const std::string &content)
{
    execute(getStatements(content));
}

void execute(std::istream &stream)
{
    execute(getStatements(stream));
}

void execute(const std::vector<std::unique_ptr<Statement>> &statements)
{
    for (const auto &s : statements)
    {
        s->execute();
    }
}
