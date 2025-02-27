#include <array>
#include "diagram.h"
#include <iostream>
#include <algorithm>

using std::size_t;
using namespace diagram;

Diagram *leaf = new Diagram(0);

static Diagram *newHeight1Diagram(const ampl::ConcreteState &state);

template <typename T>
static std::vector<T> mergeVectorsWithoutDuplicates(std::vector<T> a, std::vector<T> b);

static absi::Interval enclosure_side(Side s, const Diagram &d);

Diagram::Diagram(const size_t height) : height(height)
{
}

Diagram *Diagram::eig0(const size_t height)
{
    if (height == 0)
    {
        return leaf;
    }
    auto d = new Diagram(height);
    d->lefto(Diagram::eig0(height - 1));
    return d;
}

Diagram *Diagram::fromStateVector(const ampl::ConcreteState &state)
{
    if (state.height() == 0)
    {
        return leaf;
    }
    if (state.height() == 1)
    {
        return newHeight1Diagram(state);
    }
    auto left = Diagram::fromStateVector(state.firstHalf());
    auto right = Diagram::fromStateVector(state.secondHalf());
    auto r = new Diagram(state.height());
    r->lefto(left);
    r->righto(right);
    return r;
}

Diagram *newHeight1Diagram(const ampl::ConcreteState &state)
{
    auto r = new Diagram(1);
    if (state[0] != ampl::zero)
    {
        r->lefto(leaf, state[0]);
    }
    if (state[1] != ampl::zero)
    {
        r->righto(leaf, state[1]);
    }
    return r;
}

Evaluation Diagram::evaluate()
{
    if (height == 0)
    {
        auto ev = Evaluation(0);
        ev[0] = absi::one;
        return ev;
    }
    Evaluation arr(height); // to be returned
    // used for temporary storage
    Evaluation left_array(height - 1), right_array(height - 1), tmp(height - 1);
    for (size_t i = 0; i < tmp.size(); i++)
    {
        left_array[i] = absi::zero;
        right_array[i] = absi::zero;
        tmp[i] = absi::zero;
    }
    for (struct branch l : left)
    {
        tmp = l.d->evaluate();
        for (size_t i = 0; i < left_array.size(); i++)
        {
            left_array[i] = l.x * tmp[i] + left_array[i];
        }
    }
    for (struct branch r : right)
    {
        tmp = r.d->evaluate();
        for (size_t i = 0; i < left_array.size(); i++)
        {
            right_array[i] = r.x * tmp[i] + right_array[i];
        }
    }
    for (size_t i = 0; i < arr.size(); i++)
    {
        arr[i] = i < left_array.size() ? left_array[i] : right_array[i - left_array.size()];
    }
    return arr;
}

Diagram *Diagram::clone() const
{
    if (height == 0)
    {
        return leaf;
    }
    auto d = new Diagram(height);
    for (branch b : left)
    {
        d->lefto(b.d->clone(), b.x);
    }
    for (branch b : right)
    {
        d->righto(b.d->clone(), b.x);
    }
    return d;
}

std::vector<branch> Diagram::childrenOfSide(Side s) const
{
    return s == Side::right ? left : right;
}

void Diagram::lefto(Diagram *d, const absi::Interval& x)
{
    if (x == absi::zero)
    {
        return;
    }
    left.push_back(branch{.x = x, .d = d});
    isUpToDate = false;
    d->parents.push_back(this);
}

void Diagram::righto(Diagram *d, const absi::Interval& x)
{
    if (x == absi::zero)
    {
        return;
    }
    right.push_back(branch{.x = x, .d = d});
    isUpToDate = false;
    d->parents.push_back(this);
}

constexpr size_t Diagram::size() const
{
    return pwrtwo(height);
}

size_t Diagram::countNodesAtHeight(size_t h)
{
    auto pointers = getNodePointersAtHeight(h);
    return pointers.size();
}

// TODO: Implement this function in-place, not by copying vectors
std::vector<Diagram *> Diagram::getNodePointersAtHeight(const size_t h)
{
    std::vector<Diagram *> nodes;
    if (h > height)
    {
        throw std::invalid_argument("Height is greater than the diagram's height");
    }
    if (h == height)
    {
        nodes.push_back(this);
        return nodes;
    }
    for (branch b : left)
    {
        nodes = mergeVectorsWithoutDuplicates(nodes, b.d->getNodePointersAtHeight(h));
    }
    for (branch b : right)
    {
        nodes = mergeVectorsWithoutDuplicates(nodes, b.d->getNodePointersAtHeight(h));
    }
    return nodes;
}

void Diagram::replaceNodesAtHeight(const size_t h, Diagram *f1, Diagram *f2, Diagram *r)
{
    throw std::runtime_error("Not implemented");
}

// TODO: Implement this function in O(n log n), not in O(n^2)
template <typename T>
static std::vector<T> mergeVectorsWithoutDuplicates(const std::vector<T> a, const std::vector<T> b)
{
    std::vector<T> result;
    for (T d : a)
    {
        result.push_back(d);
    }
    for (T d : b)
    {
        if (std::find(result.begin(), result.end(), d) == result.end())
        {
            result.push_back(d);
        }
    }
    return result;
}

absi::Interval Diagram::enclosure()
{
    if (!isUpToDate)
    {
        cachedEnclosure = calculateEnclosure(*this);
        markParentsAsToBeUpdated();
        isUpToDate = true;
    }
    return cachedEnclosure;
}

void Diagram::markParentsAsToBeUpdated() const
{
    for (auto i : parents)
    {
        i->isUpToDate = false;
        i->markParentsAsToBeUpdated();
    }
}

void Diagram::forgetChild(Diagram *d) noexcept
{
    right.erase(std::remove_if(right.begin(), right.end(), [d](branch b)
                               { return b.d == d; }),
                right.end());
    left.erase(std::remove_if(left.begin(), left.end(), [d](branch b)
                              { return b.d == d; }),
               left.end());
}

Diagram::~Diagram()
{
    for (branch b : left)
    {
        delete b.d;
    }
    for (branch b : right)
    {
        delete b.d;
    }
    for (Diagram *p : parents)
    {
        p->isUpToDate = false;
        p->markParentsAsToBeUpdated();
        p->forgetChild(this);
    }
}

absi::Interval diagram::calculateEnclosure(Diagram &d)
{
    if (d.height == 0)
    {
        return absi::one;
    }
    absi::Interval l = enclosure_side(Side::left, d);
    absi::Interval r = enclosure_side(Side::right, d);
    return l | r;
}

static absi::Interval enclosure_side(Side s, const Diagram &d)
{
    absi::Interval rho = absi::zero;
    for (branch b : d.childrenOfSide(s))
    {
        absi::Interval i = b.x;
        auto j = b.d->enclosure();
        auto p = i * j;
        rho = rho + p;
    }
    return rho;
}
