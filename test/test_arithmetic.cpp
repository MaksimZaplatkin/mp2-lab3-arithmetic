// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"
#include "stack.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <map>

using namespace std;

TEST(TArithExpres, all_errors)
{
    map<char, double> values;
    values['a'] = 1;
    values['x'] = 3.14159;
    values['b'] = 2;
    values['c'] = 5;
    values['y'] = 3;
    ASSERT_ANY_THROW(TArithExpres expr1(""));
    ASSERT_ANY_THROW(TArithExpres expr2("(10 + (50 - 34)"));
    ASSERT_ANY_THROW(TArithExpres expr3("(10 + (50 - 34)))"));
    ASSERT_ANY_THROW(TArithExpres expr4("(6-4+"));
    ASSERT_ANY_THROW(TArithExpres expr5("7+"));
    ASSERT_ANY_THROW(TArithExpres expr6("5/0"));
    ASSERT_ANY_THROW(TArithExpres expr7("d"));
    ASSERT_ANY_THROW(TArithExpres exps8("sqrt(9)"));
    ASSERT_ANY_THROW(TArithExpres expr9("2@3"));
    ASSERT_ANY_THROW(TArithExpres expr10("()"));
    ASSERT_ANY_THROW(TArithExpres expr11("2..1+8.0"));
    ASSERT_ANY_THROW(TArithExpres expr12("2.+8.0"));
    ASSERT_ANY_THROW(TArithExpres expr13(".2+8.0"));
    ASSERT_ANY_THROW(TArithExpres expr14("+"));
    ASSERT_ANY_THROW(TArithExpres expr15("*"));
    ASSERT_ANY_THROW(TArithExpres expr16("sin"));
}

TEST(TArithExpres, can_create_correct_expression) 
{
    map<char, double> values;
    values['a'] = 1;
    values['x'] = 3.14159;
    values['b'] = 2;
    values['c'] = 5;
    values['y'] = 3;
    ASSERT_NO_THROW(TArithExpres expr("(a + b)/(2*sin(5/4))"));
}

TEST(TArithExpres, base_opperands)
{
    map<char, double> values;
    TArithExpres expr1("2+3");
    TArithExpres expr2("10-4");
    TArithExpres expr3("3*4");
    TArithExpres expr4("15/3");
    TArithExpres expr5("2^3");
    EXPECT_EQ(5.0, expr1.Calculate(values));
    EXPECT_EQ(6.0, expr2.Calculate(values));
    EXPECT_EQ(12.0, expr3.Calculate(values));
    EXPECT_EQ(5.0, expr4.Calculate(values));
    EXPECT_EQ(8.0, expr5.Calculate(values));
}

TEST(TArithExpres, variable)
{
    map<char, double> values;
    values['a'] = 5;
    values['b'] = 3;
    values['x'] = 3;
    values['y'] = 4;
    TArithExpres expr1("a+b");
    TArithExpres expr2("x*y-2");
    EXPECT_EQ(5.0, expr1.Calculate(values));
    EXPECT_EQ(10.0, expr2.Calculate(values));
}

TEST(TArithExpres, priority)
{
    map<char, double> values;
    TArithExpres expr1("2+3*4");
    TArithExpres expr2("(2+3)*4");
    TArithExpres expr3("10-4/2");
    TArithExpres expr4("2+3*sin(0)");
    TArithExpres expr5("(10+6)*(5-2)");
    EXPECT_EQ(14, expr1.Calculate(values));
    EXPECT_EQ(20, expr2.Calculate(values));
    EXPECT_EQ(8, expr3.Calculate(values));
    EXPECT_EQ(2, expr4.Calculate(values));
    EXPECT_EQ(48, expr5.Calculate(values));
}

TEST(TArithExpres, functions)
{
    map<char, double> values;
    values['x'] = 3.14159 / 2;
    TArithExpres expr1("sin(0)");
    TArithExpres expr2("cos(0)");
    TArithExpres expr3("sin(x)");
    EXPECT_EQ(0, expr1.Calculate(values));
    EXPECT_EQ(1, expr2.Calculate(values));
    EXPECT_NEAR(1, expr3.Calculate(values), 0.000001);
}

TEST(TArithExpres, unar)
{
    map<char, double> values;
    values['x'] =7;
    TArithExpres expr1("-5");
    TArithExpres expr2("+3");
    TArithExpres expr3("-x");
    TArithExpres expr4("5+-3");
    TArithExpres expr5("2*-4");
    TArithExpres expr6("(-5)*2");
    TArithExpres expr7("+(3+2)");
    TArithExpres expr8("--5");
    TArithExpres expr9("-+5");
    TArithExpres expr10("-sin(0)");
    TArithExpres expr11("+cos(0)");
    EXPECT_EQ(-5, expr1.Calculate(values));
    EXPECT_EQ(3, expr2.Calculate(values));
    EXPECT_EQ(-7, expr3.Calculate(values));
    EXPECT_EQ(2, expr4.Calculate(values));
    EXPECT_EQ(-8, expr5.Calculate(values));
    EXPECT_EQ(-10, expr6.Calculate(values));
    EXPECT_EQ(5, expr7.Calculate(values));
    EXPECT_EQ(5, expr8.Calculate(values));
    EXPECT_EQ(-5, expr9.Calculate(values));
    EXPECT_EQ(0, expr10.Calculate(values));
    EXPECT_EQ(1, expr11.Calculate(values));
}

TEST(TArithExpres, GetOperands)
{
    map<char, double> values;
    values['a'] = 1;
    values['x'] = 3.14159;
    values['b'] = 2;
    values['c'] = 5;
    values['y'] = 3;
    TArithExpres expr("a+b*c-sin(x)+y");
    vector<char> operands = expr.GetOperands();
    EXPECT_EQ(4, operands.size());
    EXPECT_NE(find(operands.begin(), operands.end(), "a"), operands.end());
    EXPECT_NE(find(operands.begin(), operands.end(), "b"), operands.end());
    EXPECT_NE(find(operands.begin(), operands.end(), "c"), operands.end());
    EXPECT_NE(find(operands.begin(), operands.end(), "x"), operands.end());
    EXPECT_NE(find(operands.begin(), operands.end(), "y"), operands.end());
}