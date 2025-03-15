#include <iostream>
#include <qasm.h>

/// @brief Main loop for the interpreter (interative mode)
void interpreter_main_loop();

void print_prompt();
void print_result(const std::string &result);

/// @brief Process a line of input
/// @param line The line to process
/// @return true if we should quit the program, else false
bool process_line(const std::string &line);

bool is_quit_line(const std::string &line);

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        qasm::fexec(argv[1]);
    }
    else
    {
        interpreter_main_loop();
    }
    return 0;
}

void interpreter_main_loop()
{
    std::cout << "Coto QASM Interpreter" << std::endl;
    print_prompt();
    for (std::string line; std::getline(std::cin, line);)
    {
        if (process_line(line))
        {
            break;
        }
        print_prompt();
    }
}

void print_prompt()
{
    std::cout << "| " << std::flush;
    ;
}

void print_result(const std::string &result)
{
    if (result != "")
    {
        std::cout << "- " << result << std::endl;
    }
}

bool process_line(const std::string &line)
{
    if (is_quit_line(line))
    {
        return true;
    }
    if (line.ends_with(';'))
    {
        try
        {
            qasm::exec(line);
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Failed executing line: " << e.what() << '\n';
        }
        return false;
    }
    try
    {
        if (line == "quit" || line == "exit")
        {
            return true;
        }
        print_result(qasm::eval(line));
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Failed evaluating line: " << e.what() << '\n';
    }
    return false;
}

bool is_quit_line(const std::string &line)
{
    const std::string cleaned = line.substr(0, line.find(";"));
    return cleaned == "quit" || cleaned == "exit";
}
