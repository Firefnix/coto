#include <qasm.h>

#include <qasm/execute.h>
#include <qasm/variables.h>
#include <qasm/read.h>
#include <qasm/gate.h>

#include <iostream>
#include <filesystem>

void qasm::exec(const std::string &content)
{
    execute(content);
}

void qasm::exec(std::istream &stream)
{
    execute(stream);
}

void qasm::fexec(const std::string &file_path)
{
    if (!std::filesystem::exists(file_path))
    {
        std::string fp = file_path + ".qasm";
        if (std::filesystem::exists(fp))
        {
            auto f = open_file(fp);
            exec(f);
            f.close();
            return;
        }
    }
    try
    {
        auto f = open_file(file_path);
        exec(f);
        f.close();
    }
    catch (const FileError &e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::string qasm::eval(const std::string &identifier)
{
    if (is_only_empty_characters(identifier))
    {
        return "";
    }
    try
    {
        return gate_to_string_from_name(identifier);
    }
    catch (const VariableError &e)
    {
        return var_to_string(identifier);
    }
}
