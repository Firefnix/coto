#include <qasm/execute.h>

void execute(const std::string &content)
{
    execute(parse_statements(content));
}

void execute(std::istream &stream)
{
    execute(parse_statements(stream));
}

void execute(const std::vector<std::unique_ptr<Statement>> &statements)
{
    for (const auto &s : statements)
    {
        s->execute();
    }
}
