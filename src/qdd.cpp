#include <set>
#include <qdd.h>
#include <stdio.h>
#include <amplitude.h>

using namespace qdd;

static void fillNodesPointers(std::set<std::shared_ptr<Node>>, qdd::Node, size_t, size_t);

bool Node::isUnity() const
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

size_t Node::countLeft()
{
    return left.size();
}

size_t Node::countRight()
{
    return right.size();
}

size_t Node::depth()
{
    if (countLeft())
    {
        return 1 + left.back().n->depth();
    }
    else if (countRight())
    {
        return 1 + right.back().n->depth();
    }
    return 0;
}

ampl::Amplitude qdd::Node::getAt(unsigned address, unsigned level)
{
    if (level == 0)
    {
        return ampl::one;
    }
    ampl::Amplitude a = ampl::zero;
    if ((address & (1 << (level - 1))) == 0)
    {
        puts("left");
        for (child c : left)
        {
            a += c.x * c.n->getAt(address, level - 1);
        }
        return a;
    }
    puts("right");

    for (child c : right)
    {
        a += c.x * c.n->getAt(address, level - 1);
    }
    return a;
}

size_t QDD::depth()
{
    return root.depth();
}

size_t QDD::nodesAtLevel(size_t level)
{
    std::set<std::shared_ptr<Node>> nodes;
    return nodes.size();
}

static void fillNodesPointers(std::set<std::shared_ptr<Node>> &queue, std::shared_ptr<qdd::Node> node_ptr, size_t desiredLevel, size_t currentLevel)
{
    if (currentLevel == desiredLevel)
    {
        queue.insert(node_ptr);
        return;
    }
    for (child i : node_ptr->left) {
        fillNodesPointers(queue, i.n, desiredLevel, currentLevel+1);
    }
}

size_t QDD::size()
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

ampl::Amplitude qdd::QDD::getAt(size_t address)
{
    if (address >= pow(2, depth()))
    {
        throw std::range_error("Address is larger than 2^depth");
    }
    return root_ampl * root.getAt(address, depth());
}
