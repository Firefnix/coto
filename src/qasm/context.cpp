#include <iostream>

#include <qasm/context.h>
#include <reduction.h>
#include <gateappliers.h>

struct action
{
    const Gate *gate;
    qubit q;
};

const struct action NO_ACTION = {nullptr, 0};

static Diagram *diagram = nullptr;

static qubit updateQubit(bool addOne)
{
    static qubit count = 0;
    if (addOne)
    {
        count++;
    }
    return count ? count - 1 : count;
}

qubit addQubit()
{
    return updateQubit(true);
}

std::vector<struct action> *updateAction(struct action a)
{
    static std::vector<struct action> actions;
    if (a.gate != nullptr)
        actions.push_back(a);
    return &actions;
}

void applyGate(const Gate *gate, const std::vector<qubit> &qubits)
{
    updateAction({gate, qubits[0]});
}

void createDiagram(bool implicit)
{
    if (diagram != nullptr)
    {
        delete diagram;
        std::cout << "(Deleted the previous diagram)" << std::endl;
    }
    if (implicit)
        std::cout << "(Built the diagram)" << std::endl;
    diagram = Diagram::eig0(updateQubit(false) + 1);
}

void simulate()
{
    if (diagram == nullptr)
    {
        createDiagram(true);
    }
    for (struct action a : *updateAction(NO_ACTION))
    {
        if (a.gate->name == "X")
        {
            gateappliers::applyX(diagram, a.q);
        }
        else if (a.gate->name == "H")
        {
            gateappliers::applyH(diagram, a.q);
        }
        else
        {
            std::cout << "Unimplemented gate application in context handling: " << a.gate->name << std::endl;
        }
    }
}

void printListOfActions()
{
    for (struct action a : *updateAction(NO_ACTION))
    {
        std::cout << "~ " << a.gate->name << " " << a.q << std::endl;
    }
}

void printEvaluation()
{
    if (diagram == nullptr)
        createDiagram(true);
    Evaluation eval = diagram->evaluate();
    std::cout << "\n";
    for (auto &amp : eval)
    {
        std::cout << "  ( " << amp.to_string() << " )\n";
    }
    std::cout << std::endl;
}

void freeDiagram()
{
    delete diagram;
    diagram = nullptr;
}

void printRunStatementsHelp()
{
    std::cout << "Available run statements:\n"
              << "  @build, @inst, @instantiate - create a new diagram\n"
              << "  @run, @sim, @simulate - simulate the current diagram\n"
              << "  @list, @actions - list the actions to be performed\n"
              << "  @display, @evaluate, @eval - display the evaluation of the current diagram\n"
              << "  @help, @man, @manual - display this help message\n"
              << std::endl;
}
