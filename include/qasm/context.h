/**
 * @file context.h
 * @brief Interface between the QASM interpreter and diagrams
 */
#pragma once
#include <qasm/gate.h>
#include <diagram.h>

void addQubit();

void applyGate(const Gate* gate, const std::vector<qubit>& qubits);

void createDiagram();

void simulate();

void printListOfActions();

void freeDiagram();