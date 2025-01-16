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
    return count + 1;
}

void addQubit()
{
    updateQubit(true);
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

void createDiagram()
{
    if (diagram != nullptr)
    {
        delete diagram;
    }
    diagram = Diagram::eig0(updateQubit(false)+1);
}

void simulate()
{
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
    Evaluation eval = diagram->evaluate();
    for (auto &amp : eval)
    {
        std::cout << "( " << amp.to_string() << " )\n";
    }
    std::cout << std::flush;
}

void freeDiagram()
{
    delete diagram;
    diagram = nullptr;
}
