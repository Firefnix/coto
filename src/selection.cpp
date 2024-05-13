#include <random>
#include <algorithm>

#include <selection.h>

template <size_t height, size_t h>
struct selection::mergees<h> selection::getMergeesAtHeight(Diagram<height> d, MergeesChoiceStrategy strategy)
{
    struct mergees<h> result;
    std::vector<Diagram<h>*> candidates = d.template getNodePointersAtHeight<h>();
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
}

template <size_t h>
void getRandomMergees(std::vector<Diagram<h>*> candidates, selection::mergees<h> *m)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(candidates.begin(), candidates.end(), g);
    m->a = candidates[0];
    m->b = candidates[1];
}

template <size_t h>
void getMergeesWithMaxAmplitude(std::vector<Diagram<h>*> candidates, selection::mergees<h> *m)
{
    throw std::runtime_error("Not implemented");
}

template <size_t h>
void getMergeesWithMinAmplitude(std::vector<Diagram<h>*> candidates, selection::mergees<h> *m)
{
    throw std::runtime_error("Not implemented");
}

template <size_t h>
void getMergeesWithMaxNodes(std::vector<Diagram<h>*> candidates, selection::mergees<h> *m)
{
    throw std::runtime_error("Not implemented");
}

template <size_t h>
void getMergeesWithMinNodes(std::vector<Diagram<h>*> candidates, selection::mergees<h> *m)
{
    throw std::runtime_error("Not implemented");
}