#include <durlib.h>
#include <gtest/gtest.h>

// A:
static DURLIB::Fraction Fraction_A(1, 2);
// B:
static DURLIB::Fraction Fraction_B(10, 50);
// C:
static DURLIB::Fraction Fraction_C(-1, 10);
// D:
static DURLIB::Fraction Fraction_D(10, -34);

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(DurlibFractions, TestFractionEquation1)
{
    // a / b + c / d
    const auto expected = DURLIB::Fraction(71, 25);
    const auto actual = Fraction_A / Fraction_B + Fraction_C / Fraction_D;
    ASSERT_EQ(expected, actual);
}
TEST(DurlibFractions, TestFractionEquation2)
{
    // (a * d + b * c) / (b * d)
    const auto expected = DURLIB::Fraction(71, 25);
    const auto actual = (Fraction_A * Fraction_D + Fraction_B * Fraction_C) / (Fraction_B * Fraction_D);
    ASSERT_EQ(expected, actual);
}
TEST(DurlibFractions, TestFractionEquation3)
{
    // a / b - c / d
    const auto expected = DURLIB::Fraction(54, 25);
    const auto actual = Fraction_A / Fraction_B - Fraction_C / Fraction_D;
    ASSERT_EQ(expected, actual);
}
TEST(DurlibFractions, TestFractionEquation4)
{
    // (a * d - b * c) / (b * d)
    const auto expected = DURLIB::Fraction(54, 25);
    const auto actual = (Fraction_A * Fraction_D - Fraction_B * Fraction_C) / (Fraction_B * Fraction_D);
    ASSERT_EQ(expected, actual);
}
TEST(DurlibFractions, TestFractionEquation5)
{
    // (a / b) / (c / d)
    const auto expected = DURLIB::Fraction(125, 17);
    const auto actual = (Fraction_A / Fraction_B) / (Fraction_C / Fraction_D);
    ASSERT_EQ(expected, actual);
}
TEST(DurlibFractions, TestFractionEquation6)
{
    // (a * d) / (c * b)
    const auto expected = DURLIB::Fraction(125, 17);
    const auto actual = (Fraction_A * Fraction_D) / (Fraction_C * Fraction_B);
    ASSERT_EQ(expected, actual);
}
TEST(DurlibFractions, TestFractionEquation7)
{
    // - (a / b)
    const auto expected = DURLIB::Fraction(-5, 2);
    const auto actual = -(Fraction_A / Fraction_B);
    ASSERT_EQ(expected, actual);
}
TEST(DurlibFractions, TestFractionEquation8)
{
    // (a / b) > (c / d)
    const auto expected = true;
    const auto actual = (Fraction_A / Fraction_B) > (Fraction_C / Fraction_D);
    ASSERT_EQ(expected, actual);
}
TEST(DurlibFractions, TestFractionEquation9)
{
    // (a / b) == (c / d)
    const auto expected = false;
    const auto actual = (Fraction_A / Fraction_B) == (Fraction_C / Fraction_D);
    ASSERT_EQ(expected, actual);
}