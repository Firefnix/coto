#include <reduction.h>

#include <set>

template <size_t height>
static void forceMergeAtHeight(Diagram<height> d, size_t h);

template <size_t height>
static Diagram<height> forceMerge(Diagram<height> a, Diagram<height> b);

template <size_t height>
static absi::AbstractElement get_amplitude(Diagram<height> d, branch<height> ch);

/**
 * We use a bottom-to top algorithm, reducing each level independantly.
 * At each level i, the number of nodes is reduced by one by "fusing" two nodes until
 * there is less than `maxNodes[i]` at this level.
 */
template <size_t height>
void maxNodesLevel(Diagram<height> d, std::array<size_t, height> maxNodes)
{
    for (int i = 0; i < height; i++)
    {
        while (d.nodesAtLevel(i) > maxNodes[i])
        {
            forceMergeAtHeight(d, i);
        }
    }
}

template <size_t height>
static void forceMergeAtHeight(Diagram<height> d, size_t h)
{
}

/**
 * A merging approximation.
 */
template <size_t height>
static Diagram<height> forceMerge(Diagram<height> a, Diagram<height> b)
{
    Diagram<height> result;
    std::set<std::shared_ptr<branch<height>>> leftAOnly, leftBOnly, bothLeft;
    for (branch<height - 1> ch : a.left)
    {
        auto x = get_amplitude(b, ch.d);
        if (x != absi::zero)
        {
            bothLeft.insert((ch.x | x, ch.d));
        }
        else
        {
            leftAOnly.insert(ch);
        }
    }
    for (branch<height - 1> ch : a.left)
    {
        if (not a.left.has_child(ch.d))
        {
            leftAOnly.insert(ch.d);
        }
    }
    std::set<std::shared_ptr<branch<height>>> rightAOnly, rightBOnly, bothRight;
    for (branch<height - 1> ch : a.right)
    {
        auto x = get_amplitude(b, ch.d);
        if (x != absi::zero)
        {
            bothRight.insert((ch.x | x, ch.d));
        }
        else
        {
            rightAOnly.insert(ch);
        }
    }
    for (branch<height - 1> ch : b.right)
    {
        if (getAmplitude(a.right, ch.d) == absi::zero)
        {
            rightAOnly.insert(ch);
        }
    }
    leftAOnly.insert(
        leftAOnly.end(),
        leftBOnly.begin(),
        leftBOnly.end());
    leftAOnly.insert(
        leftAOnly.end(),
        bothLeft.begin(),
        bothLeft.end());
    rightAOnly.insert(
        rightAOnly.end(),
        rightBOnly.begin(),
        rightBOnly.end());
    rightAOnly.insert(
        rightAOnly.end(),
        bothRight.begin(),
        bothRight.end());
    result.left = leftAOnly;
    result.right = rightAOnly;
    return result;
}

template <size_t height>
static absi::AbstractElement getAmplitude(std::vector<branch<height>> branches, Diagram<height - 1> possible_child)
{
    for (branch<height> b : branches)
    {
        if (b.d == possible_child)
        {
            return b.x;
        }
    }
    return absi::zero;
}