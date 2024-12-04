#include <gtest/gtest.h>
#include <qasm/read.h>
#include <qasm/execute.h>
#include <qasm/error.h>
#include <qasm/variables.h>

std::ifstream testFile(const unsigned index)
{
    return openFile("../test/qasm/test" + std::to_string(index) + ".qasm");
}

TEST(QasmTest, getStatementStrings)
{
    std::string expected[4] = {"OPENQASM 3.0", "bit a", "int b=2", "bit c"};
    auto tf = testFile(0);
    auto statements = getStatementStrings(tf);
    EXPECT_EQ(statements.size(), 4);
    for (auto i = 0; i < 4; i++)
    {
        EXPECT_EQ(statements[i].content, expected[i]);
    }
}

TEST(QasmTest, definition)
{
    EXPECT_THROW(getStatements("bit 6a;"), SyntaxError);
    EXPECT_THROW(getStatements("bit a~8;"), SyntaxError);
    EXPECT_NO_THROW(getStatements("bit my_clean_Bit887121;"));

    auto s = getStatements("int n;");
    execute(s);
    EXPECT_TRUE(varExists("n"));
}

TEST(QasmTest, assignment)
{
    EXPECT_THROW(getStatements("a!3 q=2;"), SyntaxError);
    EXPECT_THROW(getStatements("int a!3=2;"), SyntaxError);
    EXPECT_THROW(getStatements("3a=2;"), SyntaxError);

    auto s = getStatements("int n=2;");
    EXPECT_EQ(s.size(), 1);
}

TEST(QasmTest, version)
{
    EXPECT_THROW(getStatements("OPENQASM 2.0;"), VersionError);
    EXPECT_NO_THROW(getStatements("OPENQASM 3.0;"));
    EXPECT_NO_THROW(getStatements("OPENQASM 3;"));
}

TEST(QasmTest, include)
{
    EXPECT_NO_THROW(getStatements(""));
}
