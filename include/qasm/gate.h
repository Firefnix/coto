#pragma once
#include <qasm/variables.h>

#include <vector>
#include <optional>

class Gate {
public:
    static const Gate* byName(const std::string& gateName);
    void applyTo(const std::vector<varname>& qubitsNames) const;
    void applyTo(const std::vector<qubit>& qubits) const;

    /// @brief The number of qubits of the gate
    std::size_t size() const;

    std::string toString() const;

private:
    Gate(const std::string& tag, const std::size_t size);
    const std::size_t gateSize;
    const std::optional<std::string> tag;
};

std::string gateToString(const std::string& name);
