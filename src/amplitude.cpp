#include <amplitude.h>
#include <array>

std::string ampl::to_string(const ampl::Amplitude a)
{
    if (!a.imag()) {
        return std::to_string(a.real());
    }
    if (!a.real()) {
        return std::to_string(a.imag());
    }
    return std::to_string(a.real()) + "+" + std::to_string(a.imag()) + "i";
}

ampl::Amplitude ampl::random()
{
    Amplitude a;
    do {
        real r = static_cast<real>(rand()) / static_cast<real>(RAND_MAX);
        real i = static_cast<real>(rand()) / static_cast<real>(RAND_MAX);
        a = ampl::Amplitude(r, i);
    } while (abs(a) > 1);
    return a;
}

template<std::size_t size>
void ampl::randomizeState(ampl::State<size>& state)
{
    for (auto i = 0; i < size; i++) {
        state.at(i) = ampl::random();
    }
}

template class std::array<std::complex<double>, 1>;
template void ampl::randomizeState(ampl::State<1>& state);
template class std::array<std::complex<double>, 2>;
template void ampl::randomizeState(ampl::State<2>& state);
template class std::array<std::complex<double>, 4>;
template void ampl::randomizeState(ampl::State<4>& state);
template class std::array<std::complex<double>, 8>;
template void ampl::randomizeState(ampl::State<8>& state);
template class std::array<std::complex<double>, 16>;
template void ampl::randomizeState(ampl::State<16>& state);
template class std::array<std::complex<double>, 32>;
template void ampl::randomizeState(ampl::State<32>& state);
template class std::array<std::complex<double>, 64>;
template void ampl::randomizeState(ampl::State<64>& state);
template class std::array<std::complex<double>, 128>;
template void ampl::randomizeState(ampl::State<128>& state);
template class std::array<std::complex<double>, 256>;
template void ampl::randomizeState(ampl::State<256>& state);
template class std::array<std::complex<double>, 512>;
template void ampl::randomizeState(ampl::State<512>& state);
template class std::array<std::complex<double>, 1024>;
template void ampl::randomizeState(ampl::State<1024>& state);
template class std::array<std::complex<double>, 2048>;
template void ampl::randomizeState(ampl::State<2048>& state);
template class std::array<std::complex<double>, 4096>;
template void ampl::randomizeState(ampl::State<4096>& state);
template class std::array<std::complex<double>, 8192>;
template void ampl::randomizeState(ampl::State<8192>& state);
template class std::array<std::complex<double>, 16384>;
template void ampl::randomizeState(ampl::State<16384>& state);
template class std::array<std::complex<double>, 32768>;
template void ampl::randomizeState(ampl::State<32768>& state);
template class std::array<std::complex<double>, 65536>;
template void ampl::randomizeState(ampl::State<65536>& state);
template class std::array<std::complex<double>, 131072>;
template void ampl::randomizeState(ampl::State<131072>& state);
template class std::array<std::complex<double>, 262144>;
template void ampl::randomizeState(ampl::State<262144>& state);
template class std::array<std::complex<double>, 524288>;
template void ampl::randomizeState(ampl::State<524288>& state);
