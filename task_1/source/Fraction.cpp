#include "Fraction.h"

Fraction::Fraction()
    : Numerator(0), Denominator(1)
{
}

Fraction::Fraction(int num)
{
    if (num == 0)
    {
        Numerator = 0;
        Denominator = 1;
    }
    else
    {
        Denominator = 1;
        FormatFraction(num, Denominator);
    }
}

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
        FormatFraction(num, denom);
    }
}

Fraction::~Fraction()
{
}

int Fraction::GCD(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    else
    {
        return GCD(b % a, a);
    }
}

void Fraction::FormatFraction(int &num, int &denom)
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

// Function for objects to call externally.
// ADDITION
Fraction Fraction::Addition(Fraction FracRight)
{
    Numerator = Numerator * FracRight.Denominator + FracRight.Numerator * Denominator;
    Denominator = Denominator * FracRight.Denominator;
    FormatFraction(Numerator, Denominator);
    return *this;
}
Fraction Fraction::Addition(int (&FracRight)[2])
{
    Numerator = Numerator * FracRight[1] + FracRight[0] * Denominator;
    Denominator = Denominator * FracRight[1];
    FormatFraction(Numerator, Denominator);
    return *this;
}
// SUBTRACTION
Fraction Fraction::Subtraction(Fraction FracRight)
{
    Numerator = Numerator * FracRight.Denominator - FracRight.Numerator * Denominator;
    Denominator = Denominator * FracRight.Denominator;
    FormatFraction(Numerator, Denominator);
    return *this;
}
Fraction Fraction::Subtraction(int (&FracRight)[2])
{
    Numerator = Numerator * FracRight[1] - FracRight[0] * Denominator;
    Denominator = Denominator * FracRight[1];
    FormatFraction(Numerator, Denominator);
    return *this;
}
// MULTIPLICATION
Fraction Fraction::Multiplication(Fraction FracRight)
{
    Numerator = Numerator * FracRight.Numerator;
    Denominator = Denominator * FracRight.Denominator;
    FormatFraction(Numerator, Denominator);
    return *this;
}
Fraction Fraction::Multiplication(int (&FracRight)[2])
{
    Numerator = Numerator * FracRight[0];
    Denominator = Denominator * FracRight[1];
    FormatFraction(Numerator, Denominator);
    return *this;
}
// DIVISION
Fraction Fraction::Division(Fraction FracRight)
{
    Numerator = Numerator * FracRight.Denominator;
    Denominator = Denominator * FracRight.Numerator;
    FormatFraction(Numerator, Denominator);
    return *this;
}
Fraction Fraction::Division(int (&FracRight)[2])
{
    Numerator = Numerator * FracRight[0];
    Denominator = Denominator * FracRight[1];
    FormatFraction(Numerator, Denominator);
    return *this;
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
Fraction Fraction::Negative()
{
    Numerator *= -1;
    return *this;
}
// Output
void Fraction::Print()
{
    CLI_TRACE("{0}/{1}", Numerator, Denominator);
}
// Input
void Fraction::Set()
{
    CLI_INFO("Enter Fraction:");
    std::cin >> *this;
    CLI_WARN("Fraction set to {}", *this);
}
void Fraction::Set(const std::string &Temp_Fraction_Name)
{
    CLI_INFO("Enter Fraction \"{}\":", Temp_Fraction_Name);
    std::cin >> *this;
    CLI_WARN("Fraction \"{}\" set to {}", Temp_Fraction_Name, *this);
}

// Binary operations for fractions:
// Arithmetic operators:
Fraction operator+(const Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Denominator + FracRight.Numerator * FracLeft.Denominator,
                  FracLeft.Denominator * FracRight.Denominator);
    temp.FormatFraction(temp.Numerator, temp.Denominator);
    return temp;
}
Fraction operator-(const Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Denominator - FracRight.Numerator * FracLeft.Denominator,
                  FracLeft.Denominator * FracRight.Denominator);
    temp.FormatFraction(temp.Numerator, temp.Denominator);
    return temp;
}
Fraction operator*(const Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Numerator,
                  FracLeft.Denominator * FracRight.Denominator);
    temp.FormatFraction(temp.Numerator, temp.Denominator);
    return temp;
}
Fraction operator/(const Fraction &FracLeft, const Fraction &FracRight)
{
    Fraction temp(FracLeft.Numerator * FracRight.Denominator, FracLeft.Denominator * FracRight.Numerator);
    temp.FormatFraction(temp.Numerator, temp.Denominator);
    return temp;
}
// Relation operators:
bool Fraction::operator==(const Fraction &FracRight) const
{
    return ((this->Numerator == FracRight.Numerator) && (this->Denominator == FracRight.Denominator));
}
bool Fraction::operator!=(const Fraction &FracRight) const
{
    return ((this->Numerator != FracRight.Numerator) || (this->Denominator != FracRight.Denominator));
}
bool Fraction::operator>(const Fraction &FracRight) const
{
    int frac1 = this->Numerator * FracRight.Denominator;
    int frac2 = this->Denominator * FracRight.Numerator;
    return (frac1 > frac2);
}
bool Fraction::operator>=(const Fraction &FracRight) const
{
    int frac1 = this->Numerator * FracRight.Denominator;
    int frac2 = this->Denominator * FracRight.Numerator;
    return (frac1 >= frac2);
}
bool Fraction::operator<(const Fraction &FracRight) const
{
    int frac1 = this->Numerator * FracRight.Denominator;
    int frac2 = this->Denominator * FracRight.Numerator;
    return (frac1 < frac2);
}
bool Fraction::operator<=(const Fraction &FracRight) const
{
    int frac1 = this->Numerator * FracRight.Denominator;
    int frac2 = this->Denominator * FracRight.Numerator;
    return (frac1 <= frac2);
}
// Assignment operators:
Fraction operator+=(Fraction &FracLeft, const Fraction &FracRight)
{
    FracLeft = Fraction(FracLeft.Numerator * FracRight.Denominator + FracRight.Numerator * FracLeft.Denominator,
                        FracLeft.Denominator * FracRight.Denominator);
    FracLeft.FormatFraction(FracLeft.Numerator, FracLeft.Denominator);
    return FracLeft;
}
Fraction operator-=(Fraction &FracLeft, const Fraction &FracRight)
{
    FracLeft = Fraction(FracLeft.Numerator * FracRight.Denominator - FracRight.Numerator * FracLeft.Denominator,
                        FracLeft.Denominator * FracRight.Denominator);
    FracLeft.FormatFraction(FracLeft.Numerator, FracLeft.Denominator);
    return FracLeft;
}
Fraction operator*=(Fraction &FracLeft, const Fraction &FracRight)
{
    FracLeft = Fraction(FracLeft.Numerator * FracRight.Numerator, FracLeft.Denominator * FracRight.Denominator);
    FracLeft.FormatFraction(FracLeft.Numerator, FracLeft.Denominator);
    return FracLeft;
}
Fraction operator/=(Fraction &FracLeft, const Fraction &FracRight)
{
    FracLeft = Fraction(FracLeft.Numerator * FracRight.Numerator, FracLeft.Denominator * FracRight.Denominator);
    FracLeft.FormatFraction(FracLeft.Numerator, FracLeft.Denominator);
    return FracLeft;
}
// Input/Output operators:
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
        CLI_TRACE("ENTER THE FRACTION IN THIS FORMAT -> [number/number]");
        in >> input;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // CLI_INFO(" IS SPACE = {0}", DURLIB::HasWhitespace(input));
        if (input.find('/') != std::string::npos)
        {
            aText = input.substr(0, input.find('/'));
            bText = input.substr(input.find('/') + 1, input.length());
            // CLI_TRACE("A (TEXT) = {0}, B (TEXT) = {1}", aText, bText);
            if (DURLIB::CanBeInt(aText) && DURLIB::CanBeInt(bText))
            {
                a = DURLIB::STOI(aText);
                b = DURLIB::STOI(bText);
                // CLI_TRACE("A (INT) = {0}, B (INT) = {1}", a, b);
                break;
            }
            else
            {
                // CLI_ERROR("NOT NUMBERS");
                CLI_ERROR("INCORRECT FORMAT");
            }
        }
        else
        {
            CLI_ERROR("INCORRECT FORMAT");
        }
    }

    frac.Numerator = a;
    frac.Denominator = b;
    frac.FormatFraction(frac.Numerator, frac.Denominator);
    return in;
}
// Negation operator:
Fraction operator-(const Fraction &Frac)
{
    Fraction temp(Frac.Numerator * -1, Frac.Denominator);
    return temp;
}