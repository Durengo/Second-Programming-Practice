#pragma once

#include <durlib.h>

class Fraction
{
private:
    int Numerator;
    int Denominator;

    float Decimal = 0.0f;

    int GCD(int a, int b);

    void Simplify();
    void Simplify(Fraction frac);
    void Simplify(int &num, int &denom);

    void SetNumerator(int num) { Numerator = num; }
    void SetDenominator(int denom) { Denominator = denom; }

public:
    Fraction(int num, int denom);
    ~Fraction();

    void Addition(Fraction FracRight);
    void Addition(int (&FracRight)[2]);

    void Subtraction(Fraction FracRight);
    void Subtraction(int (&FracRight)[2]);

    void Multiplication(Fraction FracRight);
    void Multiplication(int (&FracRight)[2]);

    void Division(Fraction FracRight);
    void Division(int (&FracRight)[2]);

    bool More(Fraction FracRight);
    bool More(int (&FracRight)[2]);

    void Negative();

    int GetNumerator() const { return Numerator; }
    int GetDenominator() const { return Denominator; }

    void Print();

    operator int() { return (int)((int)Numerator / (int)Denominator); }
    operator float() { return ((float)Numerator / (float)Denominator); }
    operator double() { return ((double)Numerator) / (double)Denominator; }
    friend std::ostream &operator<<(std::ostream &out, const Fraction &frac);
    friend std::istream &operator>>(std::istream &in, Fraction &frac);
    friend Fraction operator+(const Fraction &FracLeft, const Fraction &FracRight);
    friend Fraction operator+=(Fraction &FracLeft, const Fraction &FracRight);
    friend Fraction operator-(const Fraction &FracLeft, const Fraction &FracRight);
    friend Fraction operator-=(Fraction &FracLeft, const Fraction &FracRight);
    friend Fraction operator*(const Fraction &FracLeft, const Fraction &FracRight);
    friend Fraction operator*=(Fraction &FracLeft, const Fraction &FracRight);
    friend Fraction operator/(const Fraction &FracLeft, const Fraction &FracRight);
    friend Fraction operator/=(Fraction &FracLeft, const Fraction &FracRight);
};

template <>
struct fmt::formatter<Fraction> : fmt::formatter<std::string>
{
    auto format(Fraction my, format_context &ctx) -> decltype(ctx.out())
    {
        if ((my.GetNumerator() % my.GetDenominator()) == 0)
        {
            return format_to(ctx.out(), "{}", my.GetNumerator() / my.GetDenominator());
        }
        else
        {
            return format_to(ctx.out(), "{}/{}", my.GetNumerator(), my.GetDenominator());
        }
    }
};