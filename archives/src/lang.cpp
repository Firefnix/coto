#include <lang.h>

A A::check(A& other) const { throw "Nope"; }
int A::value() const { return -1; }

A B::check(A& other) const { return B(n + 1); }
int B::value() const { return n; }
