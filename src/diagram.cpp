#include <array>
#include "diagram.h"
#include <iostream>

using std::size_t;

template<typename T>
static std::vector<T> mergeVectorsWithoutDuplicates(std::vector<T> a, std::vector<T> b);

template <size_t height>
Diagram<height>::Diagram()
{
}

template <size_t height>
std::array<absi::Interval, pwrtwo(height)> Diagram<height>::evaluate()
{
    const size_t N = pwrtwo(height);
    std::array<absi::Interval, N> arr;
    std::array<absi::Interval, N / 2> left_array;
    std::array<absi::Interval, N / 2> right_array;
    std::array<absi::Interval, N / 2> tmp;
    for (size_t i = 0; i < N / 2; i++)
    {
        left_array[i] = absi::zero;
        right_array[i] = absi::zero;
        tmp[i] = absi::zero;
    }
    for (struct branch<height - 1> l : left)
    {
        tmp = l.d->evaluate();
        for (size_t i = 0; i < N / 2; i++)
        {
            left_array[i] = l.x * tmp[i] + left_array[i];
        }
    }
    for (struct branch<height - 1> r : right)
    {
        tmp = r.d->evaluate();
        for (size_t i = 0; i < N / 2; i++)
        {
            std::cout << r.x.to_string() << std::endl;
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
std::array<absi::Interval, 1> Diagram<0>::evaluate()
{
    return std::array<absi::Interval, 1>{absi::one};
}

template <size_t height>
void Diagram<height>::lefto(Diagram<height - 1> *d, absi::Interval x)
{
    left.push_back(branch<height - 1>{.x = x, .d = d});
}

template <size_t height>
void Diagram<height>::righto(Diagram<height - 1> *d, absi::Interval x)
{
    right.push_back(branch<height - 1>{.x = x, .d = d});
}

template <size_t height>
size_t Diagram<height>::size()
{
    return pwrtwo(height);
}

template <size_t height>
size_t Diagram<height>::countNodesAtHeight(size_t h) {
    if (h > height) {
        throw std::invalid_argument("Height is greater than the diagram's height");
    }
    if (h == 0 || h == height) {
        return 1;
    }
    size_t n = 0;
    for (branch<height - 1> b : left) {
        n += b.d->countNodesAtHeight(h - 1);
    }
    for (branch<height - 1> b : right) {
        n += b.d->countNodesAtHeight(h - 1);
    }
    return n;
}

// TODO: Implement this function in-place, not by copying vectors
template <size_t height>
template <size_t h>
std::vector<Diagram<h>*> Diagram<height>::getNodePointersAtHeight()
{
    std::vector<Diagram<h>*> nodes;
    if (h > height) {
        throw std::invalid_argument("Height is greater than the diagram's height");
    }
    if (h == height) {
        return std::vector<Diagram<h>*>({this});
    }
    for (branch<height - 1> b : left) {
        nodes = mergeVectorsWithoutDuplicates(nodes, b.d->getNodePointersAtHeight(h - 1));
    }
    for (branch<height - 1> b : right) {
        nodes = mergeVectorsWithoutDuplicates(nodes, b.d->getNodePointersAtHeight(h - 1));
    }
    return nodes;
}

template <size_t height>
template <size_t h>
void Diagram<height>::replaceNodesAtHeight(Diagram<h> *f1, Diagram<h> *f2, Diagram<h> *r)
{
    throw std::runtime_error("Not implemented");
}

// TODO: Implement this function in O(n log n), not in O(n^2)
template <typename T>
static std::vector<T> mergeVectorsWithoutDuplicates(std::vector<T> a, std::vector<T> b) {
    std::vector<T> result;
    for (T d : a) {
        result.push_back(d);
    }
    for (T d : b) {
        if (std::find(result.begin(), result.end(), d) == result.end()) {
            result.push_back(d);
        }
    }
    return result;
}