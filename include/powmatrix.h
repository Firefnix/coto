#pragma once
#include <memory>

template <typename T>
class PowMatrix
{
private:
    /// @brief The height of the array (n)
    size_t height_;

    /// @brief The size of the array (2^n)
    size_t size_;

    /// @brief The size of the square array (2^n * 2^n)
    size_t square_size_;

    /// @brief Array data
    std::unique_ptr<T[]> data_;

public:
    /// @brief Constructor: initializes the matrix with size 2^n
    explicit PowMatrix(const size_t n);

    explicit PowMatrix(const size_t n, const T *value);

    /// @brief Access element
    T &operator()(size_t iindex, size_t jindex);

    const T &operator()(size_t iindex, size_t jindex) const;

    /// @brief Access element at row 0 and column 0 if the height is 0, otherwise throws an exception
    T value() const;

    /// @brief The matrix is of "size" 2^n x 2^n, here n is the size of the matrix
    /// @return The size of the matrix
    inline size_t height() const noexcept
    {
        return height_;
    }

    /// @brief Get size of the array
    inline size_t size() const noexcept
    {
        return size_;
    }

    PowMatrix<T> top_left() const;

    PowMatrix<T> top_right() const;

    PowMatrix<T> bottom_left() const;

    PowMatrix<T> bottom_right() const;
};
