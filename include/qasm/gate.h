/**
 * @file gate.h
 * @brief Handling QASM gates
 */
#pragma once
#include <qasm/variables.h>

#include <vector>

/// @brief A quantum gate
class Gate {
public:
    static bool exists(const std::string& gateName);
    static const Gate* byName(const std::string& gateName);
    void applyTo(const std::vector<varname>& qubitsNames) const;
    virtual void applyTo(const std::vector<qubit>& qubits) const;

    /// @brief The number of qubits of the gate
    std::size_t size() const noexcept;

    std::string toString() const noexcept;

    const std::string name;
protected:
    Gate(const std::string& name, const std::size_t size);
    const std::size_t gateSize;
};

std::string gateToString(const std::string& name);
