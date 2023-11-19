#ifndef LANG_H_
#define LANG_H_ 1

class A
{
public:
    virtual A check(A& other) const;
    virtual int value() const;
};

class B : public A
{
public:
    B(int n) : n(n) {}
    B(const B &b) { n = b.n; }
    A check(A& other) const override;
    int value() const override;

private:
    int n;
};

#endif
