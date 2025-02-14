#pragma once
#include <memory>

template <typename T>
class PowArray
{
private:
    /// @brief The height of the array (n)
    size_t height_;

    /// @brief The size of the array (2^n)
    size_t size_;

    /// @brief Array data
    std::unique_ptr<T[]> data_;

public:
    /// @brief Constructor: initializes the array with size 2^n
    explicit PowArray(size_t n);

    explicit PowArray(size_t n, T *data);

    /// @brief Access element
    T &operator[](size_t index);

    const T &operator[](size_t index) const;

    /// @brief Get height of the array
    size_t height() const;

    /// @brief Get size of the array
    size_t size() const;

    /// @brief Get pointer to the beginning of the array
    T *begin();

    /// @brief Get pointer to the beginning of the array
    const T *begin() const;

    /// @brief Get pointer to one past the end of the array
    T *end();

    /// @brief Get pointer to one past the end of the array
    const T *end() const;

    PowArray<T> firstHalf() const;

    PowArray<T> secondHalf() const;
};
