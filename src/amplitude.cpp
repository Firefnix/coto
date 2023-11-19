#include <amplitude.h>

using namespace ampl;

rational ampl::rat_int(const int i)
{
    return {i, 1};
}

RPR ampl::rpr_int(const int i)
{
    if (i >= 0)
    {
        return RPR(true, rat_int(i), rat_int(1));
    }
    return RPR(false, rat_int(-i), rat_int(1));
}

Amplitude Amplitude::conj() const
{
    return Amplitude(re, im.opposite());
}

RPR Amplitude::square_module() const
{
    return zero_rpr;
}

Amplitude ampl::ampl_int(const int i)
{
    return Amplitude(rpr_int(i), zero_rpr);
}