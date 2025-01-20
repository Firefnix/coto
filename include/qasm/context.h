/**
 * @file context.h
 * @brief Interface between the QASM interpreter and diagrams
 */
#pragma once
#include <qasm/gate.h>
#include <diagram.h>

void addQubit();

void applyGate(const Gate* gate, const std::vector<qubit>& qubits);

void createDiagram(bool implicit = false);

void simulate();

void printListOfActions();

void printEvaluation();

void freeDiagram();

void printRunStatementsHelp();
