#include <gtest/gtest.h>
#include "calculator.h" 


TEST(CalculatorTest, SimpleAddition) {
    std::string expr = "2 + 3";
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 5.0);
}

TEST(CalculatorTest, SimpleMultiplication) {
    std::string expr = "4 * 5";
    Expression e(expr);
    e.calc();
    EXPECT_EQ(e.getRes(), 20.0);
}