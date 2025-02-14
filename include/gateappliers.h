/**
 * @file gateappliers.h
 * @brief Contains functions to apply quantum gates to a diagram
 */

#include <diagram.h>
#include <qasm/variables.h>
#include <powmatrix.h>

namespace gateappliers
{
    using GateMatrix = PowMatrix<absi::Interval>;

    void applyX(Diagram *d, qubit q);

    void applyH(Diagram *d, qubit q);

    void applyS(Diagram *d, qubit a, qubit b);

    void applyCX(Diagram *d, qubit a, qubit b);

    void applyPhase(Diagram *d, qubit q, int phaseDenominator);

    void applyGateMatrix(Diagram *d, qubit q, const GateMatrix &m);
}