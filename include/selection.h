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

    template <size_t h>
    struct mergees
    {
        Diagram<h>* a;
        Diagram<h>* b;
    };

    template <size_t height, size_t h>
    struct mergees<h> getMergeesAtHeight(Diagram<height> d, MergeesChoiceStrategy strategy);
};

#endif