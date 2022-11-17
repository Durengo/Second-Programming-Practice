#pragma once

#include "durlib/Log/Log.h"

namespace DURLIB
{
    class Fraction
    {
    private:
        int Numerator;
        int Denominator;

        // Function to find the greatest common divisor using the Euclidian algorithm.
        int GCD(int a, int b);

        // Function to format the fraction (denominator cannot be less than or equal to zero; negative sign only on the numerator) and simplify the fraction if possible.
        void FormatFraction(int &num, int &denom);

    public:
        Fraction();
        Fraction(int num);
        Fraction(int num, int denom);
        ~Fraction();

        // Getters for the Numerator and Denominator.
        int GetNumerator() const { return Numerator; }
        int GetDenominator() const { return Denominator; }

        // Function for objects to call externally.
        Fraction Addition(Fraction FracRight);
        Fraction Addition(int (&FracRight)[2]);

        Fraction Subtraction(Fraction FracRight);
        Fraction Subtraction(int (&FracRight)[2]);

        Fraction Multiplication(Fraction FracRight);
        Fraction Multiplication(int (&FracRight)[2]);

        Fraction Division(Fraction FracRight);
        Fraction Division(int (&FracRight)[2]);

        bool More(Fraction FracRight);
        bool More(int (&FracRight)[2]);

        Fraction Negative();

        // Prints fraction using the overloaded << operator with durlib library logging module.
        void Print();
        // Uses input to set fraction variables with overloaded >> operator.
        void Set();
        void Set(const std::string &Temp_Fraction_Name);

        // Type conversion operations.
        // Return an integer that is the division of the numerator by the denominator (casted to double for precision) and finally rounded up.
        operator int() { return (int)std::ceil(((double)Numerator / (double)Denominator)); }
        // Return as double or float.
        operator float() { return ((float)Numerator / (float)Denominator); }
        operator double() { return ((double)Numerator) / (double)Denominator; }

        // Binary operations for fractions:
        // Arithmetic operators:
        friend Fraction operator+(const Fraction &FracLeft, const Fraction &FracRight);
        friend Fraction operator-(const Fraction &FracLeft, const Fraction &FracRight);
        friend Fraction operator*(const Fraction &FracLeft, const Fraction &FracRight);
        friend Fraction operator/(const Fraction &FracLeft, const Fraction &FracRight);

        // Relation operators:
        // C++20  OPERATORS:
        bool operator==(const Fraction &FracRight) const;
        bool operator!=(const Fraction &FracRight) const;
        bool operator>(const Fraction &FracRight) const;
        bool operator>=(const Fraction &FracRight) const;
        bool operator<(const Fraction &FracRight) const;
        bool operator<=(const Fraction &FracRight) const;
        // C++17 OPERATORS:
        // bool Fraction::operator==(const Fraction &FracRight) const;
        // bool Fraction::operator!=(const Fraction &FracRight) const;
        // bool Fraction::operator>(const Fraction &FracRight) const;
        // bool Fraction::operator>=(const Fraction &FracRight) const;
        // bool Fraction::operator<(const Fraction &FracRight) const;
        // bool Fraction::operator<=(const Fraction &FracRight) const;

        // Assignment operators:
        friend Fraction operator+=(Fraction &FracLeft, const Fraction &FracRight);
        friend Fraction operator-=(Fraction &FracLeft, const Fraction &FracRight);
        friend Fraction operator*=(Fraction &FracLeft, const Fraction &FracRight);
        friend Fraction operator/=(Fraction &FracLeft, const Fraction &FracRight);

        // Input/Output operators:
        friend std::ostream &operator<<(std::ostream &out, const Fraction &frac);
        friend std::istream &operator>>(std::istream &in, Fraction &frac);

        // Negation operator:
        friend Fraction operator-(const Fraction &Frac);
    };

}
// Formatting for fmt library.
template <>
struct fmt::formatter<DURLIB::Fraction> : fmt::formatter<std::string>
{
    auto format(DURLIB::Fraction my, format_context &ctx) -> decltype(ctx.out())
    {
        if ((my.GetNumerator() % my.GetDenominator()) == 0)
        {
            return fmt::format_to(ctx.out(), "{}/{} ({})", my.GetNumerator(), my.GetDenominator(), my.GetNumerator() / my.GetDenominator());
        }
        else
        {
            return fmt::format_to(ctx.out(), "{}/{}", my.GetNumerator(), my.GetDenominator());
        }
    }
};