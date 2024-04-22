#ifndef DIAGRAM_H
#define DIAGRAM_H 1

#include <memory>
#include <vector>

#include <absi.h>

#define pwrtwo(x) (1 << (x))

template <size_t height>
class Diagram;

/// @brief A incoming branch (in diagrams, an arrow)
/// @tparam height The height of the diagram the branch points to.
template <size_t height>
struct branch
{
    /// @brief Abstract weight on the branch
    absi::Interval x;

    /// @brief (Link to) the destination node
    Diagram<height> *d;
};

template <size_t height>
using branches = std::vector<branch<height>>;

/// @brief A general-purpose abstract-interpreted additive diagram
/// @tparam height The number of levels of the diagram. Implies having `2^height`.
template <size_t height>
class Diagram
{
public:
    Diagram();

    /// @brief Left children
    std::vector<branch<height - 1>> left;

    /// @brief Right children
    std::vector<branch<height - 1>> right;

    /// @brief Evaluate the diagram
    /// @return A mathematical vector (here an array) of 2^n intervals
    std::array<absi::Interval, pwrtwo(height)> evaluate();

    /// @brief Add @ref{d} to be a left child with amplitude @ref{x}
    /// @param d The child
    /// @param x The amplitude
    void lefto(Diagram<height - 1> *d, absi::Interval x = absi::one);

    /// @brief Add @ref{d} to be a right child with amplitude @ref{x}
    /// @param d The child
    /// @param x The amplitude
    void righto(Diagram<height - 1> *d, absi::Interval x = absi::one);

    /// @brief The number of intervals contained in the evaluation
    /// @return 2 ^ @ref{height}
    size_t size();
};

#include <../src/diagram.cpp>

#endif