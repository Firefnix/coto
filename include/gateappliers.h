#include <diagram.h>
#include <qasm/variables.h>

namespace gateappliers
{
    void applyX(Diagram *d, qubit q);

    void applyH(Diagram *d, qubit q);

    void applyS(Diagram *d, qubit a, qubit b);

    void applyCX(Diagram *d, qubit a, qubit b);
}