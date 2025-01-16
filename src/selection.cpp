#include <random>
#include <algorithm>
#include <selection.h>

void getRandomMergees(std::vector<Diagram *> candidates, selection::mergees *m)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(candidates.begin(), candidates.end(), g);
    m->a = candidates[0];
    m->b = candidates[1];
}

void getMergeesWithMaxAmplitude(std::vector<Diagram *> candidates, selection::mergees *m)
{
    throw std::runtime_error("Not implemented");
}

void getMergeesWithMinAmplitude(std::vector<Diagram *> candidates, selection::mergees *m)
{
    throw std::runtime_error("Not implemented");
}

void getMergeesWithMaxNodes(std::vector<Diagram *> candidates, selection::mergees *m)
{
    throw std::runtime_error("Not implemented");
}

void getMergeesWithMinNodes(std::vector<Diagram *> candidates, selection::mergees *m)
{
    throw std::runtime_error("Not implemented");
}

selection::mergees selection::getMergeesAtHeight(const size_t h, Diagram &d, MergeesChoiceStrategy strategy)
{
    if (h == 0)
    {
        throw std::invalid_argument("0-height diagrams have no mergees");
    }
    struct mergees result;
    std::vector<Diagram *> candidates = d.getNodePointersAtHeight(h);
    switch (strategy)
    {
    case RANDOM:
    {
        getRandomMergees(candidates, &result);
        break;
    }
    case MAX_AMPLITUDE:
    {
        getMergeesWithMaxAmplitude(candidates, &result);
        break;
    }
    case MIN_AMPLITUDE:
    {
        getMergeesWithMinAmplitude(candidates, &result);
        break;
    }
    case MAX_NODES:
    {
        getMergeesWithMaxNodes(candidates, &result);
        break;
    }
    case MIN_NODES:
    {
        getMergeesWithMinNodes(candidates, &result);
        break;
    }
    }
    return result;
}
