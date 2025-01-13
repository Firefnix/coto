#include <array>
#include "diagram.h"
#include <iostream>

using std::size_t;

template <typename T>
static std::vector<T> mergeVectorsWithoutDuplicates(std::vector<T> a, std::vector<T> b);

static absi::Interval enclosure_side(Side s, const Diagram &d);

Diagram::Diagram(const size_t height) : height(height)
{
}

template <size_t h>
Diagram *Diagram::fromStateVector(const std::span<ampl::Amplitude, pwrtwo(h)> state)
{
    auto leftSpan = std::span<ampl::Amplitude, pwrtwo(h - 1)>(state.begin(), state.begin() + pwrtwo(h - 1));
    auto rightSpan = std::span<ampl::Amplitude, pwrtwo(h - 1)>(state.begin() + pwrtwo(h - 1), state.end());
    auto left = Diagram::fromStateVector<h - 1>(leftSpan);
    auto right = Diagram::fromStateVector<h - 1>(rightSpan);
    auto r = new Diagram(h);
    r->lefto(left);
    r->righto(right);
    return r;
}

template <>
Diagram *Diagram::fromStateVector<0>(const std::span<ampl::Amplitude, pwrtwo(0)> state)
{
    auto d = new Diagram(0);
    return d;
}

template <>
Diagram *Diagram::fromStateVector<1>(const std::span<ampl::Amplitude, pwrtwo(1)> state)
{
    auto r = new Diagram(1);
    auto unity = new Diagram(0);
    if (state[0] != ampl::zero)
    {
        r->lefto(unity, Interval::singleton(state[0]));
    }
    if (state[1] != ampl::zero)
    {
        r->righto(unity, Interval::singleton(state[1]));
    }
    return r;
}

template <size_t h>
std::array<absi::Interval, pwrtwo(h)> Diagram::evaluate()
{
    const size_t N = pwrtwo(h);
    std::array<absi::Interval, N> arr;
    std::array<absi::Interval, N / 2> left_array, right_array, tmp;
    for (size_t i = 0; i < N / 2; i++)
    {
        left_array[i] = absi::zero;
        right_array[i] = absi::zero;
        tmp[i] = absi::zero;
    }
    for (struct branch l : left)
    {
        tmp = l.d->evaluate<h - 1>();
        for (size_t i = 0; i < N / 2; i++)
        {
            left_array[i] = l.x * tmp[i] + left_array[i];
        }
    }
    for (struct branch r : right)
    {
        tmp = r.d->evaluate<h - 1>();
        for (size_t i = 0; i < N / 2; i++)
        {
            right_array[i] = r.x * tmp[i] + right_array[i];
        }
    }
    for (size_t i = 0; i < N; i++)
    {
        arr[i] = i < N / 2 ? left_array[i] : right_array[i - N / 2];
    }
    return arr;
}

template <>
std::array<absi::Interval, 1> Diagram::evaluate<0>()
{
    return std::array<absi::Interval, 1>{absi::one};
}

std::vector<branch> Diagram::childrenOfSide(Side s)
{
    if (s == Side::right)
    {
        return left;
    }
    return right;
}

void Diagram::lefto(Diagram *d, absi::Interval x)
{
    left.push_back(branch{.x = x, .d = d});
    isUpToDate = false;
    d->parents.push_back(this);
}

void Diagram::righto(Diagram *d, absi::Interval x)
{
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
    if (h > height)
    {
        throw std::invalid_argument("Height is greater than the diagram's height");
    }
    if (h == 0 || h == height)
    {
        return 1;
    }
    size_t n = 0;
    for (branch b : left)
    {
        n += b.d->countNodesAtHeight(h - 1);
    }
    for (branch b : right)
    {
        n += b.d->countNodesAtHeight(h - 1);
    }
    return n;
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
static std::vector<T> mergeVectorsWithoutDuplicates(std::vector<T> a, std::vector<T> b)
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

void Diagram::markParentsAsToBeUpdated()
{
    for (auto i : parents)
    {
        i->isUpToDate = false;
        i->markParentsAsToBeUpdated();
    }
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
}

absi::Interval calculateEnclosure(Diagram &d)
{
    if (d.height == 0)
    {
        return absi::one;
    }
    absi::Interval l = enclosure_side(Side::left, d);
    absi::Interval r = enclosure_side(Side::right, d);
    return l | r;
}

static absi::Interval enclosure_side(Side s, Diagram &d)
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
