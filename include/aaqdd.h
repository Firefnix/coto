#ifndef AAQDD_H
#define AAQDD_H 1

#include <memory>
#include <vector>

#include <absi.h>

#define pwrtwo(x) (1 << (x))

template <size_t height>
class Diagram;

template <size_t height>
struct branch
{
    absi::AbstractElement x;
    std::shared_ptr<Diagram<height>> d;
};

template <size_t height>
class Diagram
{
public:
    Diagram();

    std::vector<branch<height - 1>> left;
    std::vector<branch<height - 1>> right;

    std::array<absi::AbstractElement, pwrtwo(height)> evaluate();
};

#endif