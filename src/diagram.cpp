#include <array>
#include "diagram.h"

template <size_t height>
Diagram<height>::Diagram()
{
}

template <size_t height>
std::array<absi::Interval, pwrtwo(height)> Diagram<height>::evaluate()
{
    const size_t N = pwrtwo(height);
    std::array<absi::Interval, N> arr = {absi::zero};
    std::array<absi::Interval, N / 2> left_array = {absi::zero};
    std::array<absi::Interval, N / 2> right_array = {absi::zero};
    std::array<absi::Interval, N / 2> tmp = {absi::zero};
    for (size_t i = 0; i < N / 2; i++)
    {
        left_array[i] = absi::zero;
        right_array[i] = absi::zero;
    }
    for (struct branch<height - 1> l : left)
    {
        tmp = evaluate<N / 2>(l.d);
        for (size_t i = 0; i < N / 2; i++)
        {
            left_array[i] = l.x * left_array[i] + tmp[i];
        }
    }
    for (struct branch<height - 1> r : right)
    {
        tmp = evaluate<N / 2>(r.d);
        for (size_t i = 0; i < N / 2; i++)
        {
            right_array[i] = r.x * right_array[i] + tmp[i];
        }
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