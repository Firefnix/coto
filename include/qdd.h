#ifndef QDD_H_
#define QDD_H_ 1

#include <vector>
#include <array>
#include <amplitude.h>
#include <iostream>
#include <memory>

namespace qdd
{
    class Node;
    class QDD;

    struct child
    {
        ampl::Amplitude x;
        std::shared_ptr<Node> n;
    };
    typedef std::vector<struct child> children;

    class Node
    {
        friend class QDD;

    public:
        ~Node() = default; // TODO: is that safe?

        Node(children left, children right) : left(left), right(right) {}
        Node(const Node &node) : left(node.left), right(node.right) {}
        bool isUnity() const;
        size_t countLeft();
        size_t countRight();
        size_t depth();
        void appendLeft(child c);
        void appendRight(child c);

        // private:
        ampl::Amplitude getAt(unsigned address, unsigned level);
        children left;
        children right;
    };

    static std::shared_ptr<Node> uptr = std::make_shared<Node>(new Node({}, {}));
    static Node u = *uptr; // unity

    template <std::size_t N>
    struct status_vector
    {
        typedef ampl::Amplitude values_array[N];
        values_array values;
    };

    /**
     * An additive quantum decision diagram
     */
    class QDD
    {
    public:
        template <std::size_t n>
        static QDD fromStatusVector(status_vector<n> sv);
        QDD() : root_ampl({1}), root(qdd::u) {}
        QDD(Node root) : root_ampl({1}), root(root) {}
        QDD(ampl::Amplitude root_ampl, Node root) : root_ampl(root_ampl), root(root){};
        Node root;
        ampl::Amplitude root_ampl;
        size_t depth();
        size_t size(); // in bytes
        size_t nodesAtLevel(size_t level);

        template <size_t size>
        std::array<Node *, size> save(std::array<Node, size>);

        /// @brief Get the amplitude value at given address
        /// @param address In binary, the eigenstate, e.g. 0b
        /// @return The ampliude value based on binary writing of address
        ampl::Amplitude getAt(size_t address);

    private:
        /// @brief Stores all nodes that are referenced to in the diagram
        std::vector<Node> nodes;

        template <std::size_t n>
        Node _fromStatusVectorRec(status_vector<n> sv, std::size_t begin, std::size_t end);
    };

    template <std::size_t N>
    qdd::QDD qdd::QDD::fromStatusVector(status_vector<N> sv)
    {
        auto d = QDD();
        d.root = d._fromStatusVectorRec(sv, 0, N - 1);
        return d;
    }

    template <std::size_t n>
    qdd::Node qdd::QDD::_fromStatusVectorRec(status_vector<n> sv, std::size_t begin, std::size_t end)
    {
        std::cout << "Entering rec with " << begin << " and " << end << '\n';
        if (end - begin < 2)
        {
            std::cout << "\t Finishing\n";
            return Node{(children){(struct child){sv.values[begin], uptr}}, {(struct child){sv.values[end], uptr}}};
        }
        std::size_t t = begin + (end - begin - 1) / 2;
        auto subLeft = _fromStatusVectorRec(sv, begin, t);
        Node *pleft = &nodes.emplace_back(subLeft);
        std::cout << "On left, has " << pleft << " and sizes " << subLeft.countLeft() << " and " << subLeft.countRight() << '\n';
        std::cout << "Meanwhile, *pleft has sizes " << pleft->countLeft() << " and " << pleft->countRight() << '\n';

        auto subRight = _fromStatusVectorRec(sv, t + 1, end);
        std::cout << "We are now after fsvr / before emplacement on right\n";
        std::cout << "\tL " << pleft << " and sizes " << subLeft.countLeft() << " and " << subLeft.countRight() << '\n';
        std::cout << "\tMeanwhile, *pleft has sizes " << pleft->countLeft() << " and " << pleft->countRight() << '\n';

        Node *pright = &nodes.emplace_back(subRight);
        std::cout << "We are now after fsvr / after emplacement on right\n";
        std::cout << "\tL " << pleft << " and sizes " << subLeft.countLeft() << " and " << subLeft.countRight() << '\n';
        std::cout << "\tMeanwhile, *pleft has sizes " << pleft->countLeft() << " and " << pleft->countRight() << '\n';

        std::cout << "\tR " << pright << " and sizes " << subRight.countLeft() << " and " << subRight.countRight() << '\n';
        std::cout << "\tMeanwhile, *pright has sizes " << pright->countLeft() << " and " << pright->countRight() << '\n';

        return Node(
            {(struct child){.x = ampl::one, .n = pleft}},
            {(struct child){.x = ampl::one, .n = pright}});
    };
}

#endif