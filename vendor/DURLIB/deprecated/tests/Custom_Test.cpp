#include "Fraction.h"

int main()
{
    DURLIB::Log::Init();
    CLI_TRACE("Hello, World!");

    Fraction frac1(12, 6);
    Fraction frac2(1, 2);

    CLI_TRACE("INITIAL FRACTION");
    CLI_INFO("{0}", frac1);

    CLI_TRACE("NOW ADD 1/2");
    frac1.Addition(frac2);
    CLI_INFO("{0}", frac1);

    CLI_TRACE("NOW SUBTRACT 1/2");
    frac1.Subtraction(frac2);
    CLI_INFO("{0}", frac1);
    frac1.Print();

    CLI_TRACE("NOW MULTIPLY BY 2/5");
    frac1.Multiplication({2, 5});
    frac1.Print();

    CLI_TRACE("NOW DIVIDE BY 50/37");
    frac1.Division({50, 37});
    CLI_INFO("{0}", frac1);

    CLI_WARN("IS FRAC 1 ({0}) MORE THAN 3/4? ANSWER = {1}", frac1, frac1.More({3, 4}));

    frac1.Negative();
    CLI_TRACE("FRAC 1 NEGATIVE = {0}", frac1);

    // std::cin >> frac1;
    CLI_WARN("FRAC 1 = {0}", frac1);
    frac1.Print();
    // frac1.Addition({1,-2});
    // CLI_INFO("{0}", frac1);

    CLI_TRACE("ADDITION OF {0} + {1} = {2}", frac1, frac2, frac1 + frac2);
    std::cout << frac1 + frac2 << std::endl;

    Fraction frac4(5, 6);
    Fraction frac5(-60, 80);
    CLI_TRACE("SUBTRACTION OF {0} - {1} = {2}", frac4, frac5, frac4 - frac5);
    std::cout << frac4 - frac5 << std::endl;

    CLI_TRACE("MULTIPLICATION OF {0} * {1} = {2}", frac4, frac5, frac4 * frac5);
    std::cout << frac4 * frac5 << std::endl;

    CLI_TRACE("DIVISION OF {0} / {1} = {2}", frac4, frac5, frac4 / frac5);
    std::cout << frac4 / frac5 << std::endl;

    CLI_TRACE("");
    CLI_TRACE("{0} AS INT = {1}", frac4, (int)frac4);
    CLI_TRACE("{0} AS FLOAT = {1}", frac4, (float)frac4);
    CLI_TRACE("{0} AS DOUBLE = {1}", frac4, (double)frac4);

    CLI_TRACE("frac1 = {}", frac1);
    CLI_TRACE("frac1+= OP = {}", frac1+=Fraction(74,125));

    CLI_TRACE("frac1 = {}", frac1);
    CLI_TRACE("frac1-= OP = {}", frac1-=Fraction(74,125));

    CLI_TRACE("frac1 = {}", frac1);
    CLI_TRACE("frac1*= OP = {}", frac1*=Fraction(2, 1));

    CLI_TRACE("frac1 = {}", frac1);
    CLI_TRACE("frac1/= OP = {}", frac1/=Fraction(1, 2));

    Fraction frac6(28);
    CLI_TRACE("Frac with only one int constructor = {}", frac6);


    Fraction frac7;
    CLI_TRACE("Test empty fraction = {}", frac7.Addition({1,2}).More({1,5}));

    CLI_WARN("PRESS ENTER TO EXIT.");
    std::getchar();
    return 0;
}