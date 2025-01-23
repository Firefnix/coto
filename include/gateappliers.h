/**
 * @file gateappliers.h
 * @brief Contains functions to apply quantum gates to a diagram
 */

#include <diagram.h>
#include <qasm/variables.h>

namespace gateappliers
{
    void applyX(Diagram *d, qubit q);

    void applyH(Diagram *d, qubit q);

    void applyS(Diagram *d, qubit a, qubit b);

    void applyCX(Diagram *d, qubit a, qubit b);

    void applyPhase(Diagram *d, qubit q, int phaseDenominator);
}