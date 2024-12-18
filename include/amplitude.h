#pragma once
#include <array>
#include <complex>
#define pow2(n) (1 << n)

/// @brief Handles everything related to complex numbers
namespace ampl
{
    /// @brief A class used to compute on real numbers
    typedef double real;

    /// @brief A real value of zero
    const real zero_real = 0.;

    /// @brief A real value of zero
    const real one_real = 1.;

    /** @brief A general-purpose complex amplitude
     *
     * Can use either of the x + iy or r*exp(it) representations,
     * in any case it implements the classical complex arithmetic
     * operations. Uses profusiously the `real` type.
     */
    typedef std::complex<real> Amplitude;

    template<size_t size>
    using State = std::array<ampl::Amplitude, size>;

    /** @brief Randomize a state
     *
     * Randomizes an already-allocated state (cheaper than returning by value)
     */
    template<std::size_t size>
    void randomizeState(State<size>& state)
    {
        for (auto i = 0; i < size; i++) {
            state.at(i) = random();
        }
    }

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

    /// @brief The imaginary number i
    const Amplitude i{0., 1.};
}
