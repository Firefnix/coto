#pragma once
#include <vector>
#include <complex>
#include "powarray.h"

#define pow2(n) (1 << n)

/// @brief Handles everything related to complex numbers
namespace ampl
{
    /// @brief A class used to compute on real numbers
    typedef double Real;

    /// @brief A real value of zero
    const Real zero_real = 0.;

    /// @brief A real value of zero
    const Real one_real = 1.;

    /** @brief A general-purpose complex amplitude
     *
     * Can use either of the x + iy or r*exp(it) representations,
     * in any case it implements the classical complex arithmetic
     * operations. Uses profusiously the `real` type.
     */
    typedef std::complex<Real> Amplitude;

    using ConcreteState = ampl::PowArray<Amplitude>;

    /** @brief Randomize a state
     *
     * Randomizes an already-allocated state (cheaper than returning by value)
     */
    void randomize_state(ampl::ConcreteState &state);

    /// @brief String representation of the Amplitude
    std::string to_string(const ampl::Amplitude a);

    /** @brief Generate a random amplitude
     *
     * Generate a complex number (random real and imaginary parts), normalized to have a module
     * m such that m <= 1.
     */
    Amplitude random();

    /// @brief The complex number 0
    const Amplitude zero{0., 0.};

    /// @brief The complex number 1
    const Amplitude one{1., 0.};

    /// @brief The complex number, square root of two
    const Amplitude sqrt2{std::sqrt(2), 0.};

    /// @brief The complex number, one over the square root of two
    const Amplitude inv_sqrt2{std::sqrt(1. / 2), 0.};

    /// @brief The imaginary number i
    const Amplitude i{0., 1.};
}
