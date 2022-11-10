#include "Fraction.h"

#define EQ1(A, B, C, D) (A/B+C/D)
#define EQ2(A, B, C, D) ((A*D+B*C)/B*D)
#define EQ3(A, B, C, D) (A/B-C/D)
#define EQ4(A, B, C, D) ((A*D-B*C)/(B*D))
#define EQ5(A, B, C, D) ((A/B)/(C/D))
#define EQ6(A, B, C, D) ((A*D)/(C*B))
#define EQ7(A, B, C, D) (-(A/B))
#define EQ8(A, B, C, D) ((A/B)>(C/D))
#define EQ9(A, B, C, D) ((A/B)==(C/D))

int main()
{
    DURLIB::Log::Init();

    Fraction Fraction_A, Fraction_B, Fraction_C, Fraction_D;
    CLI_TRACE("This program win run through a series of equations involving fractions.");

    Fraction_A.Set("A");
    Fraction_B.Set("B");
    Fraction_C.Set("C");
    Fraction_D.Set("D");

    CLI_WARN("FRACTIONS: A = {}, B = {}, C = {}, D = {}", Fraction_A, Fraction_B, Fraction_C, Fraction_D);
    CLI_TRACE("EQ1 - (A/B+C/D)\t\t= {}", EQ1(Fraction_A, Fraction_B, Fraction_C, Fraction_D));
    CLI_TRACE("EQ2 - ((A*D+B*C)/B*D)\t= {}", EQ2(Fraction_A, Fraction_B, Fraction_C, Fraction_D));
    CLI_TRACE("EQ3 - (A/B-C/D)\t\t= {}", EQ3(Fraction_A, Fraction_B, Fraction_C, Fraction_D));
    CLI_TRACE("EQ4 - ((A*D-B*C)/(B*D))\t= {}", EQ4(Fraction_A, Fraction_B, Fraction_C, Fraction_D));
    CLI_TRACE("EQ5 - ((A/B)/(C/D))\t= {}", EQ5(Fraction_A, Fraction_B, Fraction_C, Fraction_D));
    CLI_TRACE("EQ6 - ((A*D)/(C*B))\t= {}", EQ6(Fraction_A, Fraction_B, Fraction_C, Fraction_D));
    CLI_TRACE("EQ7 - (-(A/B))\t\t= {}", EQ7(Fraction_A, Fraction_B, Fraction_C, Fraction_D));
    CLI_TRACE("EQ8 - ((A/B)>(C/D))\t= {}", EQ8(Fraction_A, Fraction_B, Fraction_C, Fraction_D));
    CLI_TRACE("EQ9 - ((A/B)==(C/D))\t= {}", EQ9(Fraction_A, Fraction_B, Fraction_C, Fraction_D));

    CLI_WARN("PRESS ENTER TO EXIT.");
    std::getchar();
    return 0;
}