#include <gtest/gtest.h>
#include "calculator.h" 


TEST(CalculatorTest, SimpleAddition) {
    std::string expr = "2 + 3";
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 5.0);
}

TEST(CalculatorTest, SimpleAdditionWithLetters) {
    std::string expr = "a + b";
    Expression e(expr);
    e.calc({ {"a",2},{"b",3} });
    EXPECT_EQ(e.getRes(), 5.0);
}

TEST(CalculatorTest, OperationWithTooManyNumbers) {
    std::string expr = "a + b";
    Expression e(expr);
    EXPECT_ANY_THROW(e.calc({ {"a",2},{"b",3},{"c",4} }));
}

TEST(CalculatorTest, OperationWithTooLittleNumbers) {
    std::string expr = "a + b";
    Expression e(expr);
    EXPECT_ANY_THROW(e.calc({ {"a" , 2} }));
}

TEST(CalculatorTest, SimpleMultiplication) {
    std::string expr = "4 * 5";
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 20.0);
}

TEST(CalculatorTest, SimpleMultiplicationWithLetter) {
    std::string expr = "a * b";
    Expression e(expr);
    e.calc({ { "a",4 }, { "b",5 } });
    EXPECT_EQ(e.getRes(), 20.0);
}

TEST(CalculatorTest, DivizionByZero) {
    std::string expr = "10 / 0";
    Expression e(expr);
    EXPECT_ANY_THROW(e.calc());
}

TEST(CalculatorTest, DivizionByZeroWithLetters) {
    std::string expr = "c + a / b";
    Expression e(expr);
    EXPECT_ANY_THROW(e.calc({ {"a",2},{"b",0},{"c",7}}));
}

TEST(CalculatorTest, UnaryFunctions) {
    std::string expr = "sqrt 16";
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 4.0);
}

TEST(CalculatorTest, Factorial) {
    std::string expr = "5 !";
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 120.0);
}

TEST(CalculatorTest, PriorityTest) {
    std::string expr = "2 + 2 * 2";
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 6.0);
}

TEST(CalculatorTest, BracketsTest) {
    std::string expr = "(2 + 2) * 2";
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 8.0);
}

TEST(CalculatorTest, PowerTest) {
    std::string expr = "2 ^ 3"; 
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 8.0);
}

TEST(CalculatorTest, UnaryFunctionsWithLetters) {
    std::string expr = "sqrt x + 2";
    Expression e(expr);
    e.calc({ {"x", 16} });
    EXPECT_EQ(e.getRes(), 6.0);
}

TEST(CalculatorTest, FactorialWithLetters) {
    std::string expr = "x ! * 2";
    Expression e(expr);
    e.calc({ {"x", 5} });
    EXPECT_EQ(e.getRes(), 240.0);
}

TEST(CalculatorTest, PriorityTestWithLetters) {
    std::string expr = "a + b * c";
    Expression e(expr);
    e.calc({ {"a", 2}, {"b", 2}, {"c", 2} });
    EXPECT_EQ(e.getRes(), 6.0);
}

TEST(CalculatorTest, BracketsTestWithLetters) {
    std::string expr = "( a + b ) * c";
    Expression e(expr);
    e.calc({ {"a", 2}, {"b", 2}, {"c", 2} });
    EXPECT_EQ(e.getRes(), 8.0);
}

TEST(CalculatorTest, PowerTestWithLetters) {
    std::string expr = "a ^ b";
    Expression e(expr);
    e.calc({ {"a", 2}, {"b", 3} });
    EXPECT_EQ(e.getRes(), 8.0);
}