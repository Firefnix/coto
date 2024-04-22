#include <array>
#include "diagram.h"
#include <iostream>

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
