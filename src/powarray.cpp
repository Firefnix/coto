#include <powarray.h>

using ampl::PowArray;

template <typename T>
PowArray<T>::PowArray(size_t n)
{
    if (n >= sizeof(size_t) * 8)
    {
        throw std::overflow_error("Exponent too large"); // Prevent overflow
    }
    height_ = n;
    size_ = static_cast<size_t>(1) << n; // Compute 2^n
    data_ = std::make_unique<T[]>(size_);
}

template <typename T>
PowArray<T>::PowArray(size_t n, const T *data)
{
    if (n >= sizeof(size_t) * 8)
    {
        throw std::overflow_error("Exponent too large"); // Prevent overflow
    }
    height_ = n;
    size_ = static_cast<size_t>(1) << n; // Compute 2^n
    data_ = std::make_unique<T[]>(size_);
    for (size_t i = 0; i < size_; i++)
    {
        data_[i] = data[i];
    }
}

template <typename T>
T &PowArray<T>::operator[](size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return data_[index];
}

template <typename T>
const T &PowArray<T>::operator[](size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return data_[index];
}

template <typename T>
size_t PowArray<T>::height() const noexcept
{
    return height_;
}

template <typename T>
size_t PowArray<T>::size() const noexcept
{
    return size_;
}

template <typename T>
T *PowArray<T>::begin() noexcept
{
    return data_.get();
}

template <typename T>
const T *PowArray<T>::begin() const noexcept
{
    return data_.get();
}

template <typename T>
T *PowArray<T>::end() noexcept
{
    return data_.get() + size_;
}

template <typename T>
const T *PowArray<T>::end() const noexcept
{
    return data_.get() + size_;
}

template <typename T>
PowArray<T> PowArray<T>::first_half() const
{
    auto half = PowArray(height_ - 1);
    for (size_t i = 0; i < half.size(); i++)
    {
        half[i] = data_[i];
    }
    return half;
}

template <typename T>
PowArray<T> PowArray<T>::second_half() const
{
    auto half = PowArray(height_ - 1);
    for (size_t i = 0; i < half.size(); i++)
    {
        half[i] = data_[half.size() + i];
    }
    return half;
}

#include "amplitude.h"
#include "absi.h"

template class ampl::PowArray<ampl::Amplitude>;
template class ampl::PowArray<absi::Interval>;
