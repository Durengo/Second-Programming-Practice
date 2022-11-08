#include "Fraction.h"

Fraction::Fraction(int num, int denom)
{
    if (denom == 0)
    {
        CLI_ERROR("DIVISION BY 0 (ZERO) IS IMPOSSIBLE.");
        CLI_ASSERT(0, "DIVISION BY 0");
        return;
    }
    else if (num == 0)
    {
        Numerator = 0;
        Denominator = 1;
    }
    else
    {
        Simplify(num, denom);
    }
}

Fraction::~Fraction()
{
}

int Fraction::GCD(int a, int b)
{
    if (a == 0)
        return b;
    return GCD(b % a, a);
}

void Fraction::Simplify()
{
    int temp = GCD(Numerator, Denominator);
    Numerator = Numerator / temp;
    Denominator = Denominator / temp;
}

void Fraction::Simplify(Fraction frac)
{
    int sign = 1;
    if (frac.Numerator < 0)
    {
        sign *= -1;
        frac.Numerator *= -1;
    }
    if (frac.Denominator < 0)
    {
        sign *= -1;
        frac.Denominator *= -1;
    }
    int temp = GCD(frac.Numerator, frac.Denominator);
    frac.Numerator = frac.Numerator / temp * sign;
    frac.Denominator = frac.Denominator / temp;
}

void Fraction::Simplify(int &num, int &denom)
{
    int sign = 1;
    if (num < 0)
    {
        sign *= -1;
        num *= -1;
    }
    if (denom < 0)
    {
        sign *= -1;
        denom *= -1;
    }
    int temp = GCD(num, denom);
    Numerator = num / temp * sign;
    Denominator = denom / temp;
}

// ADDITION
void Fraction::Addition(Fraction FracRight)
{
    Numerator = Numerator * FracRight.Denominator + FracRight.Numerator * Denominator;
    Denominator = Denominator * FracRight.Denominator;
    Simplify();
}
void Fraction::Addition(int (&FracRight)[2])
{
    Numerator = Numerator * FracRight[1] + FracRight[0] * Denominator;
    Denominator = Denominator * FracRight[1];
    Simplify();
}
// SUBTRACTION
void Fraction::Subtraction(Fraction FracRight)
{
    Numerator = Numerator * FracRight.Denominator - FracRight.Numerator * Denominator;
    Denominator = Denominator * FracRight.Denominator;
    Simplify();
}
void Fraction::Subtraction(int (&FracRight)[2])
{
    Numerator = Numerator * FracRight[1] - FracRight[0] * Denominator;
    Denominator = Denominator * FracRight[1];
    Simplify();
}
// MULTIPLICATION
void Fraction::Multiplication(Fraction FracRight)
{
    Numerator = Numerator * FracRight.Numerator;
    Denominator = Denominator * FracRight.Denominator;
    Simplify();
}
void Fraction::Multiplication(int (&FracRight)[2])
{
    Numerator = Numerator * FracRight[0];
    Denominator = Denominator * FracRight[1];
    Simplify();
}
// DIVISION
void Fraction::Division(Fraction FracRight)
{
    Numerator = Numerator * FracRight.Denominator;
    Denominator = Denominator * FracRight.Numerator;
    Simplify();
}
void Fraction::Division(int (&FracRight)[2])
{
    Numerator = Numerator * FracRight[0];
    Denominator = Denominator * FracRight[1];
    Simplify();
}
// MORE
bool Fraction::More(Fraction FracRight)
{
    int frac1 = Numerator * FracRight.Denominator;
    int frac2 = Denominator * FracRight.Numerator;

    return frac1 > frac2;
}
bool Fraction::More(int (&FracRight)[2])
{
    int frac1 = Numerator * FracRight[1];
    int frac2 = Denominator * FracRight[0];

    return frac1 > frac2;
}
// NEGATIVE
void Fraction::Negative()
{
    Numerator *= -1;
}
void Fraction::Print()
{
    CLI_TRACE("{0}/{1}", Numerator, Denominator);
}

std::ostream &operator<<(std::ostream &out, const Fraction &frac)
{
    if (frac.Denominator == 1)
    {
        out << frac.Numerator;
    }
    else
    {
        out << frac.Numerator << "/" << frac.Denominator;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Fraction &frac)
{
    std::string input;
    std::string aText, bText;
    int a = 0, b = 0;
    while (true)
    {
        CLI_TRACE("PLEASE ENTER THE FRACTION [number/number]");
        in >> input;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        CLI_INFO(" IS SPACE = {0}", DURLIB::HasWhitespace(input));
        if (input.find('/') != std::string::npos)
        {
            aText = input.substr(0, input.find('/'));
            bText = input.substr(input.find('/') + 1, input.length());
            CLI_TRACE("A (TEXT) = {0}, B (TEXT) = {1}", aText, bText);
            if (DURLIB::CanBeInt(aText) && DURLIB::CanBeInt(bText))
            {
                a = DURLIB::STOI(aText);
                b = DURLIB::STOI(bText);
                CLI_TRACE("A (INT) = {0}, B (INT) = {1}", a, b);
                break;
            }
            else
            {
                CLI_ERROR("NOT NUMBERS");
            }
        }
        else
        {
            CLI_ERROR("INCORRECT FORMAT");
        }
    }

    frac.Numerator = a;
    frac.Denominator = b;
    return in;
}

Fraction operator+(const Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Denominator + FracRight.Numerator * FracLeft.Denominator,
                  FracLeft.Denominator * FracRight.Denominator);
    temp.Simplify(temp.Numerator, temp.Denominator);
    // CLI_WARN("FRACTION = {0}", temp);
    return temp;
}

Fraction operator+=(Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Denominator + FracRight.Numerator * FracLeft.Denominator,
                  FracLeft.Denominator * FracRight.Denominator);
    FracLeft = temp;
    // FracLeft.Simplify(FracLeft.Numerator, FracLeft.Denominator);
    //  CLI_WARN("FRACTION = {0}", temp);
    return FracLeft;
}

Fraction operator-(const Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Denominator - FracRight.Numerator * FracLeft.Denominator,
                  FracLeft.Denominator * FracRight.Denominator);
    temp.Simplify(temp.Numerator, temp.Denominator);

    return temp;
}

Fraction operator-=(Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Denominator - FracRight.Numerator * FracLeft.Denominator,
                  FracLeft.Denominator * FracRight.Denominator);
    FracLeft = temp;
    // temp.Simplify(temp.Numerator, temp.Denominator);

    return FracLeft;
}

Fraction operator*(const Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Numerator,
                  FracLeft.Denominator * FracRight.Denominator);
    return temp;
}

Fraction operator*=(Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Numerator,
                  FracLeft.Denominator * FracRight.Denominator);
    FracLeft = temp;
    return FracLeft;
}

Fraction operator/(const Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Denominator,
                  FracLeft.Denominator * FracRight.Numerator);
    return temp;
}

Fraction operator/=(Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Numerator,
                  FracLeft.Denominator * FracRight.Denominator);
    FracLeft = temp;
    return FracLeft;
}