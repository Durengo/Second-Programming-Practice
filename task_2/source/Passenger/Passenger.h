#pragma once

#include "Human.h"
#include "Luggage.h"

#include <string>

// Currently not very meaningful in any calculation but if some sort of ticket system is implemented the age group could dictate how much the ticket costs.
enum AgeGroup
{
    Adult = 0,
    Child = 1
};

// Convert enum to a char* (string)
const char *AgeGroupEnumToText(AgeGroup ageGroup);

// This class inherits the human and the luggage classes. This class combines both of the previous classes into a single class for better portability.
// This class also calculates the body weight and the luggage weight and adds it into a single value.

class Passenger : public Human, public Luggage
{
private:
    AgeGroup AgeType;
    // Human Weight + Luggage
    double TotalWeight;

public:
    Passenger(const std::string &name, const std::string &surname, const DURLIB::DateMath::DateYMD &birthday, double bodyWeight);
    Passenger(const std::string &name, const std::string &surname, const DURLIB::DateMath::DateYMD &birthday);
    ~Passenger();

    // Prints base class human information and total weight.
    void PrintHumanInformation() override;

    // GETTERS & SETTERS:

    AgeGroup GetAgeGroup() const { return AgeType; }

    double GetTotalWeight() const { return BodyWeight + LuggageWeight; }

    // HUMAN INHERITANCE OVERRIDES:
    void SetBodyWeight(double bodyWeight) override;

    // LUGGAGE INHERITANCE OVERRIDES:
    void SetLuggageWeight(double weight) override;
    void AddLuggageWeight(double weight) override;
    void RemoveLuggageWeight(double weight) override;

private:
    void SetAgeGroup();
};