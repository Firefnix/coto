#include <aaqdd.h>

template <size_t height>
Diagram<height>::Diagram()
{
}

template <size_t height>
std::array<absi::AbstractElement, pwrtwo(height)> Diagram<height>::evaluate()
{
    const size_t N = pwrtwo(height);
    std::array<absi::AbstractElement, N> arr;
    std::array<absi::AbstractElement, N / 2> left_array, right_array;
    std::array<absi::AbstractElement, N / 2> tmp;
    for (size_t i = 0; i < N / 2; i++)
    {
        left_array[i] = absi::zero;
        right_array[i] = absi::zero;
    }
    for (struct branch<height - 1> l : left)
    {
        tmp = evaluate_N<N / 2>(l.d);
        for (size_t i = 0; i < N / 2; i++)
        {
            left_array[i] = l.x * left_array[i] + tmp[i];
        }
    }
    for (struct branch<height - 1> r : right)
    {
        tmp = evaluate_N<N / 2>(r.d);
        for (size_t i = 0; i < N / 2; i++)
        {
            right_array[i] = r.x * right_array[i] + tmp[i];
        }
    }
    return arr;
}