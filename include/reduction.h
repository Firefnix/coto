#ifndef RECUDTCION_H_
#define REDUCTION_H_ 1

#include <diagram.h>

/**
 * @brief A module packaging multiple reduction methods for quantum decision diagrams
 */
namespace reduction
{
    /** @brief Reduces the number of nodes at each level of the QDD so that level i
     * contains less than (or equal) `maxNodes[i]]`.
     * @param d The quantum diagram we want to reduce
     * @param maxNodes A vector containing the max number of nodes for each level
     * @return Nothing, the reduction is in-place
     */
    template <std::size_t height>
    void maxNodesLevel(Diagram<height> d, std::array<size_t, height> maxNodes);
};

#endif