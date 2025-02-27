/**
 * @file diagram.h
 * @brief Abstract-interpreted additive diagrams
 */
#pragma once
#include <vector>
#include <absi.h>
#include <amplitude.h>

#define pwrtwo(x) (1 << (x))

using absi::Interval;
using std::size_t;

enum Side
{
    left,
    right
};

class Diagram;

/// @brief A incoming branch (in diagrams, an arrow)
/// @tparam height The height of the diagram the branch points to.
struct branch
{
    /// @brief Abstract weight on the branch
    absi::Interval x;

    /// @brief (Link to) the destination node
    Diagram *d;

    bool operator<(const branch &b) const
    {
        return d < b.d;
    }
};

using branches = std::vector<branch>;

using Evaluation = ampl::PowArray<Interval>;

/// @brief A general-purpose abstract-interpreted additive diagram
/// @tparam height The number of levels of the diagram. Implies having `2^height`.
class Diagram
{
public:
    /// @brief Create an empty diagram with no children
    Diagram(const size_t height);

    static Diagram *fromStateVector(const ampl::ConcreteState &state);

    static Diagram *eig0(const size_t height);

    /// @brief Create a random diagram
    /// Creates a random diagram. The values on the branches always have a
    /// modulus less than 1. This function is not deterministic. The distributions
    /// used to choose the number of children and the amplitudes are undefined in this
    /// interface and are left as an implementation detail that is subject to change.
    /// @return A random diagram
    static Diagram random(const size_t height);

    /// @brief Children of side @p s
    std::vector<branch> childrenOfSide(Side s) const;

    /// @brief Evaluate the diagram
    /// @return A mathematical vector (here a std::vector) of 2^n intervals
    Evaluation evaluate();

    /// @brief Clone the diagram
    /// @return A new diagram with the same structure
    Diagram *clone();

    /// @brief Add @p d to be a left child with amplitude @p x
    /// @param d The child
    /// @param x The amplitude
    void lefto(Diagram *d, Interval x = absi::one);

    /// @brief Add @p d to be a right child with amplitude @p x
    /// @param d The child
    /// @param x The amplitude
    void righto(Diagram *d, Interval x = absi::one);

    /// @brief The number of intervals contained in the evaluation
    /// @return 2 ^ @p height
    constexpr size_t size() const;

    /// @brief The number of nodes at a given height
    size_t countNodesAtHeight(size_t h);

    /// @brief Get all nodes at a given height
    std::vector<Diagram *> getNodePointersAtHeight(const size_t h);

    /// @brief Replace nodes @p f1 and @p f2 by @p r at a given height
    void replaceNodesAtHeight(const size_t h, Diagram *f1, Diagram *f2, Diagram *r);

    /// @brief An interval that contains all the intervals of the evaluation.
    Interval enclosure();

    /// @brief A positive number
    absi::real imprecision();

    ~Diagram();

    void markParentsAsToBeUpdated();


    /// @brief Is the data stored at node-level up-to-date
    bool isUpToDate = false;

    const size_t height;

    /// @brief Left children
    branches left;

    /// @brief Right children
    branches right;

protected:
    /// @brief Populate the diagram with random values
    void populate(const size_t totalHeight = 0);

    /// @brief The enclosure value if `isUpToDate` is true
    Interval cachedEnclosure;

    /** @brief The parents of the node
     * @details This is used to propagate changes in the children to the parents. righto and lefto
     * should update the parents of the children.
    */
    std::vector<Diagram *> parents;

    /// @brief Forget a child
    void forgetChild(Diagram *d) noexcept;
};

Interval calculateEnclosure(Diagram &d);

const size_t CHILDREN_NUMBER_AMBITION = 5;