#include "powarray.h"

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
size_t PowArray<T>::height() const
{
    return height_;
}

template <typename T>
size_t PowArray<T>::size() const
{
    return size_;
}

template <typename T>
T *PowArray<T>::begin()
{
    return data_.get();
}

template <typename T>
const T *PowArray<T>::begin() const
{
    return data_.get();
}

template <typename T>
T *PowArray<T>::end()
{
    return data_.get() + size_;
}

template <typename T>
const T *PowArray<T>::end() const
{
    return data_.get() + size_;
}

template <typename T>
PowArray<T> PowArray<T>::firstHalf() const
{
    auto half = PowArray(height_ - 1);
    for (size_t i = 0; i < half.size(); i++)
    {
        half[i] = data_[i];
    }
    return half;
}

template <typename T>
PowArray<T> PowArray<T>::secondHalf() const
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

template class PowArray<ampl::Amplitude>;
template class PowArray<absi::Interval>;
