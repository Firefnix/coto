#ifndef AMPLITUDE_H_
#define AMPLITUDE_H_ 1

#include <complex>

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

    std::string to_string(Amplitude a);

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

    /// @brief A fast-exponentiation function
    /// @param n The exponent
    /// @return 2 to the power of n
    std::size_t
    pow2(std::size_t n);
}

#endif