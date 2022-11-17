#pragma once

#include <durlib/Datatype/Date/DateMath.h>

#include <string>

// Human class is the base of the passenger class. It includes the basic human information like name, surname and date of birth.
// Body weight is included because it will be taken into account when calculating the fuel costs for flights.

class Human
{
protected:
    std::string Name;
    std::string Surname;
    DURLIB::DateMath::DateYMD DateOfBirth;
    int Age;
    double BodyWeight;

public:
    Human(const std::string &name, const std::string &surname, const DURLIB::DateMath::DateYMD &birthday, double bodyWeight);
    Human(const std::string &name, const std::string &surname, const DURLIB::DateMath::DateYMD &birthday);
    virtual ~Human();

    virtual void PrintHumanInformation();

    // GETTERS & SETTERS:
    std::string GetName() const { return Name; }

    std::string GetSurname() const { return Surname; }

    DURLIB::DateMath::DateYMD GetDateOfBirth() const { return DateOfBirth; }

    int GetAge() const { return Age; }

    double GetBodyWeight() const { return BodyWeight; }

    virtual void SetBodyWeight(double bodyWeight) { BodyWeight = bodyWeight; }
};