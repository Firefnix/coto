#include <reduction.h>

#include <set>
#include <algorithm>

using diagram::Diagram, diagram::branch, diagram::branches;

static void forceMergeAtHeight(Diagram d, const size_t h, selection::MergeesChoiceStrategy strategy);

static absi::Interval childAmplitude(branches brs, Diagram *possible_child);

void reduction::cutDeadBranches(Diagram *d)
{
    for (size_t i = 1; i < d->height + 1; i++)
    {
        for (auto node : d->getNodePointersAtHeight(i))
        {
            for (auto i = 0; i < node->left.size(); i++)
            {
                if ((node->left[i]).d->left.size() == 0 && (node->left[i]).d->right.size() == 0)
                {
                    node->left.erase(node->left.begin() + i);
                    delete (node->left[i]).d;
                }
            }
            for (auto i = 0; i < node->right.size(); i++)
            {
                if ((node->right[i]).d->left.size() == 0 && (node->right[i]).d->right.size() == 0)
                {
                    node->right.erase(node->right.begin() + i);
                    delete (node->right[i]).d;
                }
            }
        }
    }
}

/**
 * @brief Reduces the diagram according to the sizes in @ref{maxNodes}.
 * We use a bottom-to top algorithm, reducing each level independantly.
 * At each level i, the number of nodes is reduced by one by "fusing" two nodes until
 * there is less than `maxNodes[i]` at this level.
 */
template <size_t height>
void reduction::maxNodesLevel(Diagram d, std::array<size_t, height> maxNodes, selection::MergeesChoiceStrategy strategy)
{
    for (size_t i = 0; i < height; i++)
    {
        while (d.countNodesAtHeight(i) > maxNodes[i])
        {
            forceMergeAtHeight(d, i, strategy);
        }
    }
}

template <size_t height>
static void forceMergeAtHeight(Diagram d, const size_t h, selection::MergeesChoiceStrategy strategy)
{
    struct mergees hMergees = selection::getMergeesAtHeight(h, d, strategy);
    Diagram result = reduction::forceMerge(*hMergees.a, *hMergees.b);
    d.replaceNodesAtHeight(h, *hMergees.a, *hMergees.b, result);
}

/// @brief An approximation algorithm for non-additive QDDs
/// We apply @ref{forceMerge} to nodes of same descendance, top to down, every time it is needed.
/// @tparam height The height of the diagram we want to reduce
/// @param d The diagram we want to reduce
template <size_t height>
void algo1(Diagram d, std::array<size_t, height> maxNodes, selection::MergeesChoiceStrategy strategy)
{
    for (size_t i = 0; i < height; i++)
    {
        while (d.countNodesAtHeight(i) > maxNodes[i])
        {
            forceMergeAtHeight(d, i, strategy);
        }
    }
}

Diagram reduction::forceMerge(Diagram &a, Diagram &b)
{
    if (a.height != b.height)
    {
        throw std::invalid_argument("Trying to merge diagrams with different heights");
    }
    Diagram result(a.height);
    std::set<branch> leftAOnly, leftBOnly, bothLeft;
    for (branch aBranch : a.left)
    {
        auto x = childAmplitude(b.left, aBranch.d);
        if (x != absi::zero)
        {
            bothLeft.insert({aBranch.x | x, aBranch.d});
        }
        else
        {
            leftAOnly.insert(aBranch);
        }
    }
    for (branch bBranch : a.left)
    {
        if (childAmplitude(a.left, bBranch.d) == absi::zero)
        {
            leftBOnly.insert(bBranch);
        }
    }
    std::set<branch> rightAOnly, rightBOnly, bothRight;
    for (branch aBranch : a.right)
    {
        auto x = childAmplitude(b.right, aBranch.d);
        if (x != absi::zero)
        {
            bothRight.insert({aBranch.x | x, aBranch.d});
        }
        else
        {
            rightAOnly.insert(aBranch);
        }
    }
    for (branch bBranch : a.right)
    {
        if (childAmplitude(a.right, bBranch.d) == absi::zero)
        {
            rightBOnly.insert(bBranch);
        }
    }
    leftAOnly.insert(leftBOnly.begin(), leftBOnly.end());
    leftAOnly.insert(bothLeft.begin(), bothLeft.end());
    rightAOnly.insert(rightBOnly.begin(), rightBOnly.end());
    rightAOnly.insert(bothRight.begin(), bothRight.end());
    for (auto cBranch : leftAOnly)
    {
        result.left.push_back(cBranch);
    }
    for (auto cBranch : rightAOnly)
    {
        result.right.push_back(cBranch);
    }
    return result;
}

static absi::Interval childAmplitude(branches brs, Diagram *possible_child)
{
    for (branch b : brs)
    {
        if (b.d == possible_child)
        {
            return b.x;
        }
    }
    return absi::zero;
}