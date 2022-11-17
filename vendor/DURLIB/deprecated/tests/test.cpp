#include <iostream>

#include "Fraction.h"

// A:
const Fraction Fraction_A(1, 2);
// B:
const Fraction Fraction_B(10, 50);
// C:
const Fraction Fraction_C(-1, 10);
// D:
const Fraction Fraction_D(10, -34);

// EXPECTED VALUES:
// FIRST EQUATION
// a / b + c / d
const Fraction First_Equation_Expected_Value(71, 25);
// SECOND EQUATION
// (a * d + b * c) / (b * d)
const Fraction Second_Equation_Expected_Value(71, 25);
// THIRD EQUATION
// a / b - c / d
const Fraction Third_Equation_Expected_Value(54, 25);
// FOURTH EQUATION
// (a * d - b * c) / (b * d)
const Fraction Fourth_Equation_Expected_Value(54, 25);
// FIFTH EQUATION
// (a / b) / (c / d)
const Fraction Fifth_Equation_Expected_Value(125, 17);
// SIXTH EQUATION
// (a * d) / (c * b)
const Fraction Sixth_Equation_Expected_Value(125, 17);
// SEVENTH EQUATION
// - (a / b)
const Fraction Seventh_Equation_Expected_Value(-5, 2);
// EIGHTH EQUATION
// (a / b) > (c / d)
const bool Eighth_Equation_Expected_Value = true;
// NINTH EQUATION
// (a / b) == (c / d)
const bool Ninth_Equation_Expected_Value = false;

// EQUATIONS:
// FIRST EQUATION
int Test_First_Equation();
// SECOND EQUATION
int Test_Second_Equation();
// THIRD EQUATION
int Test_Third_Equation();
// FOURTH EQUATION
int Test_Fourth_Equation();
// FIFTH EQUATION
int Test_Fifth_Equation();
// SIXTH EQUATION
int Test_Sixth_Equation();
// SEVENTH EQUATION
int Test_Seventh_Equation();
// EIGHTH EQUATION
int Test_Eighth_Equation();
// NINTH EQUATION
int Test_Ninth_Equation();

int main(int argc, char **argv)
{
    DURLIB::Log::Init();
    std::cout << std::endl;
    int TestValue = -1;
    std::string CurrentTest = "";
    int SuccessCounter = 0;

    ////////////////////////////////////
    // FIRST EQUATION TEST///////////////
    ////////////////////////////////////
    CurrentTest = "a / b + c / d";
    TestValue = Test_First_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // FIRST EQUATION TEST///////////////
    ////////////////////////////////////

    ////////////////////////////////////
    // SECOND EQUATION TEST//////////////
    ////////////////////////////////////
    CurrentTest = "(a * d + b * c) / (b * d)";
    TestValue = Test_Second_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // SECOND EQUATION TEST//////////////
    ////////////////////////////////////

    ////////////////////////////////////
    // THIRD EQUATION TEST///////////////
    ////////////////////////////////////
    CurrentTest = "a / b - c / d";
    TestValue = Test_Third_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // THIRD EQUATION TEST///////////////
    ////////////////////////////////////

    ////////////////////////////////////
    // FOURTH EQUATION TEST//////////////
    ////////////////////////////////////
    CurrentTest = "(a * d - b * c) / (b * d)";
    TestValue = Test_Fourth_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // FOURTH EQUATION TEST//////////////
    ////////////////////////////////////

    ////////////////////////////////////
    // FIFTH EQUATION TEST///////////////
    ////////////////////////////////////
    CurrentTest = "(a / b) / (c / d)";
    TestValue = Test_Fifth_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // FIFTH EQUATION TEST///////////////
    ////////////////////////////////////

    ////////////////////////////////////
    // SIXTH EQUATION TEST///////////////
    ////////////////////////////////////
    CurrentTest = "(a * d) / (c * b)";
    TestValue = Test_Sixth_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // SIXTH EQUATION TEST///////////////
    ////////////////////////////////////

    ////////////////////////////////////
    // SEVENTH EQUATION TEST/////////////
    ////////////////////////////////////
    CurrentTest = "- (a / b)";
    TestValue = Test_Seventh_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // SEVENTH EQUATION TEST/////////////
    ////////////////////////////////////

    ////////////////////////////////////
    // EIGHT EQUATION TEST///////////////
    ////////////////////////////////////
    CurrentTest = "(a / b) > (c / d)";
    TestValue = Test_Eighth_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // EIGHT EQUATION TEST///////////////
    ////////////////////////////////////

    ////////////////////////////////////
    // NINTH EQUATION TEST///////////////
    ////////////////////////////////////
    CurrentTest = "(a / b) == (c / d)";
    TestValue = Test_Ninth_Equation();
    if (TestValue == 0)
    {
        CLI_INFO("{0} = {1}", CurrentTest, TestValue);
        SuccessCounter++;
    }
    else
    {
        CLI_ERROR("{0} = {1}", CurrentTest, TestValue);
    }
    std::cout << std::endl;
    ////////////////////////////////////
    // NINTH EQUATION TEST///////////////
    ////////////////////////////////////

    CLI_INFO("SUCCESSFUL TESTS: {0} OUT OF {1}", SuccessCounter, 9);
    CLI_ERROR("FAILED TESTS: {0}", 9 - SuccessCounter);

    CLI_WARN("PRESS ENTER TO EXIT.");
    std::getchar();
    return 0;
}

int Test_First_Equation()
{
    CLI_WARN("FIRST EQUATION TEST BEGIN");

    Fraction actual = Fraction_A / Fraction_B + Fraction_C / Fraction_D;

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", First_Equation_Expected_Value, actual);
    if (First_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Test_Second_Equation()
{
    CLI_WARN("SECOND EQUATION TEST BEGIN");

    Fraction actual = (Fraction_A * Fraction_D + Fraction_B * Fraction_C) / (Fraction_B * Fraction_D);

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", Second_Equation_Expected_Value, actual);
    if (Second_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Test_Third_Equation()
{
    CLI_WARN("THIRD EQUATION TEST BEGIN");

    Fraction actual = Fraction_A / Fraction_B - Fraction_C / Fraction_D;

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", Third_Equation_Expected_Value, actual);
    if (Third_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Test_Fourth_Equation()
{
    CLI_WARN("FOURTH EQUATION TEST BEGIN");

    Fraction actual = (Fraction_A * Fraction_D - Fraction_B * Fraction_C) / (Fraction_B * Fraction_D);

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", Fourth_Equation_Expected_Value, actual);
    if (Fourth_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Test_Fifth_Equation()
{
    CLI_WARN("FIFTH EQUATION TEST BEGIN");

    Fraction actual = (Fraction_A/Fraction_B)/(Fraction_C/Fraction_D);

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", Fifth_Equation_Expected_Value, actual);
    if (Fifth_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Test_Sixth_Equation()
{
    CLI_WARN("SIXTH EQUATION TEST BEGIN");

    Fraction actual = (Fraction_A*Fraction_D)/(Fraction_C*Fraction_B);

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", Sixth_Equation_Expected_Value, actual);
    if (Sixth_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Test_Seventh_Equation()
{
    CLI_WARN("SEVENTH EQUATION TEST BEGIN");

    Fraction actual = -(Fraction_A/Fraction_B);

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", Seventh_Equation_Expected_Value, actual);
    if (Seventh_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Test_Eighth_Equation()
{
    CLI_WARN("EIGHTH EQUATION TEST BEGIN");

    bool actual = (Fraction_A/Fraction_B)>(Fraction_C/Fraction_D);

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", Eighth_Equation_Expected_Value, actual);
    if (Eighth_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Test_Ninth_Equation()
{
    CLI_WARN("NINTH EQUATION TEST BEGIN");

    bool actual = (Fraction_A/Fraction_B) == (Fraction_C/Fraction_D);

    CLI_TRACE("\nEXPECTED\t = {0}\nACTUAL\t\t = {1}", Ninth_Equation_Expected_Value, actual);
    if (Ninth_Equation_Expected_Value != actual)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}