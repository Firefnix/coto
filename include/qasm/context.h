/**
 * @file context.h
 * @brief Interface between the QASM interpreter and diagrams
 */
#pragma once
#include <qasm/gate.h>
#include <diagram.h>

qubit add_qubit();

void apply_gate(const Gate* gate, const std::vector<qubit>& qubits);

void create_diagram(bool implicit = false);

void simulate();

void print_list_of_actions();

void print_evaluation();

void print_diagram_description();

void free_diagram();

void print_run_statements_help();
