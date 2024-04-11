#ifndef DIAGRAM_H
#define DIAGRAM_H 1

#include <memory>
#include <vector>

#include <absi.h>

#define pwrtwo(x) (1 << (x))

template <size_t height>
class Diagram;

template <size_t height>
struct branch
{
    absi::Interval x;
    std::shared_ptr<Diagram<height>> d;
};

/// @brief 
/// @tparam height The number of levels of the diagram. Implies having `2^height`.
template <size_t height>
class Diagram
{
public:
    Diagram();

    std::vector<branch<height - 1>> left;
    std::vector<branch<height - 1>> right;

    std::array<absi::Interval, pwrtwo(height)> evaluate();
};

#endif