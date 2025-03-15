/**
 * @file gate.h
 * @brief Handling QASM gates
 */
#pragma once
#include <qasm/variables.h>

#include <vector>

/// @brief A quantum gate
class Gate
{
public:
    [[nodiscard]] static bool exists(const std::string &gateName) noexcept;
    [[nodiscard]] static const Gate from_name(const std::string &gateName);
    void apply_to(const std::vector<varname> &qubits_names) const;
    virtual void apply_to(const std::vector<qubit> &qubits) const;

    /// @brief The number of qubits of the gate
    std::size_t size() const noexcept;

    std::string to_string() const noexcept;

    const std::string name;

protected:
    Gate(const std::string &name, const std::size_t size);
    const std::size_t gate_size;
};

/// @brief A phase gate
class PhaseGate : public Gate
{
public:
    [[nodiscard]] static bool is(const std::string &gateName);
    PhaseGate(const std::string &gateName);

    const int phase;

protected:
    PhaseGate(int phase);
};

std::string gate_to_string_from_name(const std::string &name);
