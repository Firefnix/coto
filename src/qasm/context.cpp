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
const struct action CLEAR_ACTION = {nullptr, 1};

static diagram::Diagram *mainDiagram = nullptr;

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
    if (a.gate == nullptr)
    {
        if (a.q == CLEAR_ACTION.q)
            actions.clear();
    }
    else
    {
        actions.push_back(a);
    }
    return &actions;
}

void applyGate(const Gate *gate, const std::vector<qubit> &qubits)
{
    updateAction({gate, qubits[0]});
}

void createDiagram(bool implicit)
{
    if (mainDiagram != nullptr)
    {
        delete mainDiagram;
        std::cout << "(Deleted the previous diagram)" << std::endl;
    }
    if (implicit)
        std::cout << "(Built the diagram)" << std::endl;
    mainDiagram = diagram::Diagram::eig0(updateQubit(false) + 1);
}

void simulate()
{
    if (mainDiagram == nullptr)
    {
        createDiagram(true);
    }
    for (struct action a : *updateAction(NO_ACTION))
    {
        if (a.gate->name == "x")
        {
            gateappliers::applyX(mainDiagram, a.q);
        }
        else if (a.gate->name == "h")
        {
            gateappliers::applyH(mainDiagram, a.q);
        }
        else if (a.gate->name == "s")
        {
            gateappliers::applyS(mainDiagram, a.q, a.q + 1);
        }
        else if (a.gate->name == "cx")
        {
            gateappliers::applyCX(mainDiagram, a.q, a.q + 1);
        }
        else if (a.gate->name[0] == 'p')
        {
            int phase = dynamic_cast<const PhaseGate *>(a.gate)->phase;
            gateappliers::applyPhase(mainDiagram, a.q, phase);
        }
        else
        {
            std::cout << "Unimplemented gate application in context handling: " << a.gate->name << std::endl;
        }
    }
    updateAction(CLEAR_ACTION);
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
    if (mainDiagram == nullptr)
        createDiagram(true);
    diagram::Evaluation eval = mainDiagram->evaluate();
    std::cout << "\n";
    for (auto &amp : eval)
    {
        std::cout << "  ( " << amp.to_string() << " )\n";
    }
    std::cout << std::endl;
}

static void registerNodes(diagram::Diagram *d, std::set<diagram::Diagram *> &seen)
{
    seen.insert(d);
    for (auto &b : d->left)
    {
        if (seen.find(b.d) == seen.end())
        {
            seen.insert(b.d);
            registerNodes(b.d, seen);
        }
    }
    for (auto &b : d->right)
    {
        if (seen.find(b.d) == seen.end())
        {
            seen.insert(b.d);
            registerNodes(b.d, seen);
        }
    }
}

static size_t getBranchCount(diagram::Diagram *d)
{
    size_t count = 0;
    for (auto &b : d->left)
    {
        count += getBranchCount(b.d);
        count++;
    }
    for (auto &b : d->right)
    {
        count += getBranchCount(b.d);
        count++;
    }
    return count;
}

void printDiagramDescription()
{
    if (mainDiagram == nullptr)
    {
        std::cout << "(null)" << std::endl;
        return;
    }
    std::set<diagram::Diagram *> seen;
    registerNodes(mainDiagram, seen);
    std::cout << "~ height " << mainDiagram->height << std::endl;
    std::cout << "~ nodes " << seen.size() << std::endl;
    std::cout << "~ branches " << getBranchCount(mainDiagram) << std::endl;
}

void freeDiagram()
{
    delete mainDiagram;
    mainDiagram = nullptr;
}

void printRunStatementsHelp()
{
    std::cout << "Available run statements:\n"
              << "  @build, @inst, @instantiate - create a new diagram\n"
              << "  @run, @sim, @simulate - simulate the current diagram\n"
              << "  @list, @actions - list the actions to be performed\n"
              << "  @display, @evaluate, @eval - display the evaluation of the current diagram\n"
              << "  @describe, @desc - display the description of the current diagram\n"
              << "  @help, @man, @manual - display this help message\n"
              << std::endl;
}
