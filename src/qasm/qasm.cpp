#include <qasm.h>

#include <qasm/execute.h>
#include <qasm/variables.h>
#include <qasm/read.h>
#include <qasm/gate.h>

#include <filesystem>

void qasm::exec(const std::string& content)
{
    execute(content);
}

void qasm::exec(std::istream& stream)
{
    execute(stream);
}

void qasm::fexec(const std::string& filePath)
{
    if (!std::filesystem::exists(filePath)) {
        std::string fp = filePath + ".qasm";
        if (std::filesystem::exists(fp)) {
            auto f = openFile(fp);
            exec(f);
            f.close();
            return;
        }
    }
    auto f = openFile(filePath);
    exec(f);
    f.close();
}

std::string qasm::eval(const std::string& identifier)
{
    try {
        return gateToString(identifier);
    } catch (const VariableError& e) {
        return varToString(identifier);
    }
}
