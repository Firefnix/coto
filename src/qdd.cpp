#include <qdd.h>
#include <amplitude.h>

using namespace qdd;

bool Node::is_unity() const
{
    return left.empty() && right.empty();
}

void Node::appendLeft(child c)
{
    left.push_back(c);
}

void Node::appendRight(child c)
{
    right.push_back(c);
}

unsigned Node::countLeft()
{
    return left.size();
}

unsigned Node::countRight()
{
    return right.size();
}

unsigned Node::depth()
{
    if (!left.empty())
    {
        return left.back().n->depth();
    }
    else if (!right.empty())
    {
        return right.back().n->depth();
    }
    return 0;
}

unsigned QDD::depth()
{
    return root.depth();
}

unsigned QDD::size()
{
    return sizeof(child); // TODO: implement that
}

template <size_t s>
std::array<Node *, s> QDD::save(std::array<Node, s> newNodes)
{
    std::array<Node *, s> pointers;
    for (size_t i = 0; i < s; i++)
    {
        nodes.push_back(newNodes[i]);
        pointers[i] = &(nodes.back());
    }
    return pointers;
}

static ampl::Amplitude _getAt(unsigned address, unsigned level, Node n);

ampl::Amplitude QDD::getAt(unsigned int address)
{
    return _getAt(address, depth(), root);
}

static ampl::Amplitude _getAt(unsigned address, unsigned level, Node n)
{
    return ampl::zero;
}
 