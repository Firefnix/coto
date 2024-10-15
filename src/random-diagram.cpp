#include "diagram.h"
#include <random>

using engine = std::mt19937;

const size_t CHILDREN_NUMBER_AMBITION = 5;

static size_t maxChildrenNumber(size_t height, size_t totalHeight);

static size_t minChildrenNumber(size_t height, size_t totalHeight);

template <size_t height>
Diagram<height> Diagram<height>::random()
{
    Diagram<height> d;
    d.populate(height);
    return d;
}

template <>
void Diagram<0>::populate(size_t totalHeight)
{
    return;
}

template <size_t height>
void Diagram<height>::populate(size_t totalHeight)
{
    static std::random_device dev;
    static engine rng(dev());
    std::uniform_real_distribution<double> amplRng(0.0, 1.0);
    std::uniform_int_distribution<size_t> childrenNumberRng(
        minChildrenNumber(height, totalHeight),
        maxChildrenNumber(height, totalHeight)
    );
    for (size_t i = 0; i < childrenNumberRng(rng); i++)
    {
        auto *d = new Diagram<height - 1>();
        d->populate(totalHeight ? totalHeight - 1 : 0);
        lefto(d, absi::Interval::real(amplRng(rng)));
    }
    for (size_t i = 0; i < childrenNumberRng(rng); i++)
    {
        auto *d = new Diagram<height - 1>();
        d->populate(totalHeight ? totalHeight - 1 : 0);
        righto(d, absi::Interval::real(amplRng(rng)));
    }
}

static size_t maxChildrenNumber(size_t height, size_t totalHeight)
{
    if (totalHeight == 0) {
        return CHILDREN_NUMBER_AMBITION;
    }
    if (height < totalHeight / 2) {
        return 2 * height * CHILDREN_NUMBER_AMBITION / totalHeight + 1;
    }
    return 2 * (totalHeight - height) * CHILDREN_NUMBER_AMBITION / totalHeight + 1;
}

static size_t minChildrenNumber(size_t height, size_t totalHeight)
{
    // Could also be max / 2
    auto half = maxChildrenNumber(height, totalHeight) / 2;
    return half ? half : 1;
    if (totalHeight == 0) {
        return CHILDREN_NUMBER_AMBITION;
    }
   if (height < totalHeight / 2) {
        return 2 * height / totalHeight + 1;
    }
    return 2 * (totalHeight - height) / totalHeight + 1;
}
