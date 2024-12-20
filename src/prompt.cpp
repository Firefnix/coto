#include <iostream>
#include <qasm.h>

void printPrompt();

/// @brief Process a line of input
/// @param line The line to process
/// @return true if we should quit the program, else false
bool processLine(const std::string& line);

bool isQuitLine(const std::string& line);

int main(int argc, char* argv[])
{
    std::cout << "Coto QASM Interpreter" << std::endl;
    printPrompt();
    for (std::string line; std::getline(std::cin, line);) {
        if (processLine(line)) {
            break;
        }
        printPrompt();
    }
    return 0;
}

void printPrompt()
{
    std::cout << "| " << std::flush;;
}

bool processLine(const std::string& line)
{
    if (isQuitLine(line)) {
        return true;
    }
    if (line.ends_with(';')) {
        try
        {
            qasm::exec(line);
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << "Failed executing line: " << e.what() << '\n';
        }
        return false;
    }
    try
    {
        if (line == "quit" || line == "exit") {
            return true;
        }
        const std::string result = qasm::eval(line);
        if (result != "") {
            std::cout << result << std::endl;
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Failed evaluating line: " << e.what() << '\n';
    }
    return false;
}

bool isQuitLine(const std::string& line)
{
    const std::string cleaned = line.substr(0, line.find(";"));
    return cleaned == "quit" || cleaned == "exit";
}
