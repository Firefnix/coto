#pragma once
#include <memory>
#include <vector>
#include <span>

#include <absi.h>

#define pwrtwo(x) (1 << (x))

using std::size_t;
using absi::Interval;

enum Side { left, right };

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
    /// @brief Create an empty diagram with no children
    Diagram();

    static Diagram<height>* fromStateVector(const std::span<ampl::Amplitude, pwrtwo(height)> state);

    /// @brief Create a random diagram
    /// Creates a random diagram. The values on the branches always have a
    /// modulus less than 1. This function is not deterministic. The distributions
    /// used to choose the number of children and the amplitudes are undefined in this
    /// interface and are left as an implementation detail that is subject to change.
    /// @return A random diagram
    static Diagram<height> random();

    static Diagram<height>* randomPointer();

    /// @brief Populate the diagram with random values
    void populate(size_t totalHeight = 0);

    /// @brief Children of side @p s
    std::vector<branch<height - 1>> childrenOfSide(Side s);

    /// @brief Evaluate the diagram
    /// @return A mathematical vector (here an array) of 2^n intervals
    std::array<Interval, pwrtwo(height)> evaluate();

    /// @brief Add @p d to be a left child with amplitude @p x
    /// @param d The child
    /// @param x The amplitude
    void lefto(Diagram<height - 1> *d, Interval x = absi::one);

    /// @brief Add @p d to be a right child with amplitude @p x
    /// @param d The child
    /// @param x The amplitude
    void righto(Diagram<height - 1> *d, Interval x = absi::one);

    /// @brief The number of intervals contained in the evaluation
    /// @return 2 ^ @p height
    constexpr size_t size() const;

    /// @brief The number of nodes at a given height
    size_t countNodesAtHeight(size_t h);

    /// @brief Get all nodes at a given height
    template <size_t h>
    std::vector<Diagram<h>*> getNodePointersAtHeight();

    /// @brief Replace nodes @p f1 and @p f2 by @p r at a given height
    template <size_t h>
    void replaceNodesAtHeight(Diagram<h> *f1, Diagram<h> *f2, Diagram<h> *r);

    /// @brief An interval that contains all the intervals of the evaluation.
    Interval enclosure();

    /// @brief A positive number
    absi::real imprecision();

    ~Diagram();

    void markParentsAsToBeUpdated();

    std::vector<Diagram<height+1> *> parents;

    /// @brief Is the data stored at node-level up-to-date
    bool isUpToDate = false;

protected:
    /// @brief Left children
    std::vector<branch<height - 1>> left;

    /// @brief Right children
    std::vector<branch<height - 1>> right;

    /// @brief The enclosure value if `isUpToDate` is true
    Interval cachedEnclosure;
};

template<size_t height>
Interval calculateEnclosure(Diagram<height>& d);

#include <../src/diagram.cpp>

#include <../src/random-diagram.cpp>
