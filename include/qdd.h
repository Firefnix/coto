#ifndef QDD_H_
#define QDD_H_ 1

#include <vector>
#include <array>
#include <amplitude.h>

namespace qdd
{
    class Node;

    struct child
    {
        ampl::Amplitude x;
        Node *n;
    };
    typedef std::vector<struct child> children;

    class Node
    {
    public:
        Node(children left, children right) : left(left), right(right) {}
        Node(const Node &node) : left(node.left), right(node.right) {}
        void appendLeft(child c);
        void appendRight(child c);
        unsigned int countLeft();
        unsigned int countRight();
        bool is_unity() const;
        unsigned int depth();

    private:
        children left;
        children right;
    };

    Node u = Node({}, {}); // unity

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
        unsigned depth();
        unsigned size(); // in bytes

        template <size_t size>
        std::array<Node *, size> save(std::array<Node, size>);
        ampl::Amplitude getAt(unsigned int address);

    private:
        template <std::size_t n>
        Node _fromStatusVectorRec(status_vector<n> sv, std::size_t begin, std::size_t end);
        std::vector<Node> nodes;
    };

    template <std::size_t n>
    qdd::QDD qdd::QDD::fromStatusVector(status_vector<n> sv)
    {
        auto d = QDD();
        d.root = d._fromStatusVectorRec(sv, 0, n - 1);
        return d;
    }

    template <std::size_t n>
    qdd::Node qdd::QDD::_fromStatusVectorRec(status_vector<n> sv, std::size_t begin, std::size_t end)
    {
        if (end - begin < 2)
        {
            return Node{(children){(struct child){sv.values[begin], &qdd::u}}, {(struct child){sv.values[begin + 1], &qdd::u}}};
        }
        std::size_t t = begin + (end - begin - 1) / 2;
        auto sub = _fromStatusVectorRec(sv, begin, t);
        nodes.push_back(sub);
        Node *pleft = &nodes.back();
        nodes.push_back(_fromStatusVectorRec(sv, t + 1, end));
        Node *pright = &nodes.back();

        return Node(
            {(struct child){ampl::one, pleft}},
            {(struct child){ampl::one, pleft}});
    };
}

#endif