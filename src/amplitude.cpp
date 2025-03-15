#include <amplitude.h>
#include <array>

std::string ampl::to_string(const ampl::Amplitude a)
{
    if (!a.imag())
    {
        return std::to_string(a.real());
    }
    if (!a.real())
    {
        return std::to_string(a.imag());
    }
    return std::to_string(a.real()) + "+" + std::to_string(a.imag()) + "i";
}

ampl::Amplitude ampl::random()
{
    Amplitude a;
    do
    {
        Real r = static_cast<Real>(rand()) / static_cast<Real>(RAND_MAX);
        Real i = static_cast<Real>(rand()) / static_cast<Real>(RAND_MAX);
        a = ampl::Amplitude(r, i);
    } while (abs(a) > 1);
    return a;
}

void ampl::randomize_state(ConcreteState &state)
{
    for (auto i = 0; i < state.size(); i++)
    {
        state[i] = random();
    }
}
