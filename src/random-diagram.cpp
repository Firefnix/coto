#include "diagram.h"
#include <random>

using engine = std::mt19937;

static size_t maxChildrenNumber(size_t height, size_t totalHeight);

static size_t minChildrenNumber(size_t height, size_t totalHeight);

Diagram Diagram::random(const size_t height)
{
    Diagram d(height);
    d.populate(height);
    return d;
}

Diagram* Diagram::randomPointer(const size_t height)
{
    auto d = new Diagram(height);
    d->populate(height);
    return d;
}

void Diagram::populate(const size_t totalHeight)
{
    if (height == 0) {
        return;
    }
    static std::random_device dev;
    static engine rng(dev());
    std::uniform_real_distribution<double> amplRng(0.0, 1.0);
    std::uniform_int_distribution<size_t> childrenNumberRng(
        minChildrenNumber(height, totalHeight),
        maxChildrenNumber(height, totalHeight)
    );
    for (size_t i = 0; i < childrenNumberRng(rng); i++)
    {
        auto *d = new Diagram(height - 1);
        d->populate(totalHeight ? totalHeight - 1 : 0);
        lefto(d, absi::Interval::real(amplRng(rng)));
    }
    for (size_t i = 0; i < childrenNumberRng(rng); i++)
    {
        auto *d = new Diagram(height - 1);
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
