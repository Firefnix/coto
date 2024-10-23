/**
 * @brief Contains functions and classes related to selection operations on mergees in diagrams.
 */
#ifndef SELECTION_H_
#define SELECTION_H_ 1

#include <diagram.h>

namespace selection {
      /**
     * @brief Enumeration of strategies for choosing mergees.
     */
    enum MergeesChoiceStrategy
    {
        RANDOM,         /**< Randomly choose mergees. */
        MAX_AMPLITUDE,  /**< Choose mergees with maximum amplitude. */
        MIN_AMPLITUDE,  /**< Choose mergees with minimum amplitude. */
        MAX_NODES,     /**< Choose mergees with maximum number of nodes. */
        MIN_NODES      /**< Choose mergees with minimum number of nodes. */
    };

    /**
     * @brief Struct containing two Diagram pointers.
     * @tparam h The height of the Diagrams.
     */
    template <size_t h>
    struct mergees
    {
        Diagram<h>* a;
        Diagram<h>* b;
    };

    /**
     * @brief Get the mergees at a certain height in a Diagram.
     * 
     * @tparam height The height of the Diagram.
     * @tparam h The height at which to get the mergees.
     * @param d The Diagram.
     * @param strategy The strategy to use for choosing the mergees.
     * @return struct mergees<h> The mergees.
     */
    template <size_t h, size_t height>
    mergees<h> getMergeesAtHeight(Diagram<height>& d, MergeesChoiceStrategy strategy);

    template <size_t height>
    mergees<0> getMergeesAtHeight(Diagram<height>& d, MergeesChoiceStrategy strategy);
};

#include <../src/selection.cpp>

#endif