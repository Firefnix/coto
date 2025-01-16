#include <gtest/gtest.h>
#include <qasm.h>
#include <qasm/error.h>

using namespace qasm;

TEST(QasmTest, definition)
{
    EXPECT_THROW(exec("bit 6a;"), SyntaxError);
    EXPECT_THROW(exec("bit a~8;"), SyntaxError);
    EXPECT_NO_THROW(exec("bit my_clean_Bit887121;"));

    exec("int n;");
    EXPECT_NO_THROW(eval("n"));

    EXPECT_THROW(exec("int X;"), VariableError);
}

TEST(QasmTest, assignment)
{
    EXPECT_THROW(exec("a!3 q=2;"), SyntaxError);
    EXPECT_THROW(exec("int a!3=2;"), SyntaxError);
    EXPECT_THROW(exec("3a=2;"), SyntaxError);

    exec("int n=2;");
    EXPECT_EQ(eval("n"), "int: 2");

    exec("bit a=1;");
    EXPECT_EQ(eval("a"), "bit: 1");

    EXPECT_THROW(exec("qubit q=0;"), VariableError);
}

TEST(QasmTest, version)
{
    EXPECT_THROW(exec("OPENQASM 2.0;"), VersionError);
    EXPECT_NO_THROW(exec("OPENQASM 3.0;"));
    EXPECT_NO_THROW(exec("OPENQASM 3;"));
}

TEST(QasmTest, include)
{
    EXPECT_NO_THROW(exec("include \"file.qasm\""));
}

TEST(QasmTest, qubits)
{
    exec("qubit a;");
    exec("qubit b;");
    EXPECT_EQ(eval("a"), "qubit: 0");
    EXPECT_EQ(eval("b"), "qubit: 1");
}

TEST(QasmTest, commonGates)
{
    EXPECT_EQ(eval("X"), "gate: X[1]");
    EXPECT_EQ(eval("H"), "gate: H[1]");
    EXPECT_EQ(eval("CX"), "gate: CX[2]");
    EXPECT_EQ(eval("S"), "gate: S[2]");
}