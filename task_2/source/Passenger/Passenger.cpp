#include "Passenger.h"

#include <durlib/Log/Log.h>

const char *AgeGroupEnumToText(AgeGroup ageGroup)
{
    switch (ageGroup)
    {
    case AgeGroup::Adult:
        return "Adult";
        break;
    case AgeGroup::Child:
        return "Child";
        break;
    default:
        CLI_ASSERT(0, "AGE GROUP ENUM LOGIC OUT OF BOUNDS.")
        return "-1";
    }
}

Passenger::Passenger(const std::string &name, const std::string &surname, const DURLIB::DateMath::DateYMD &birthday, double bodyWeight)
    : Human(name, surname, birthday, bodyWeight), Luggage(), TotalWeight(0)
{
    TotalWeight += BodyWeight;
    SetAgeGroup();
    // DEBUG_TRACE("NEW PASSENGER CREATED! NAME: {}, SURNAME: {}, DATE OF BIRTH: {}, AGE: {}, AGE GROUP: {}, TOTAL WEIGHT: {}", Name, Surname, DateOfBirth, Age, AgeGroupEnumToText(AgeType), TotalWeight);
}

Passenger::Passenger(const std::string &name, const std::string &surname, const DURLIB::DateMath::DateYMD &birthday)
    : Human(name, surname, birthday), Luggage(), TotalWeight(0)
{
    SetAgeGroup();
    // DEBUG_TRACE("NEW PASSENGER CREATED! NAME: {}, SURNAME: {}, DATE OF BIRTH: {}, AGE: {}, AGE GROUP: {}, TOTAL WEIGHT: {}", Name, Surname, DateOfBirth, Age, AgeGroupEnumToText(AgeType), TotalWeight);
}

Passenger::~Passenger()
{
}

void Passenger::SetAgeGroup()
{
    if (Age > 16)
    {
        AgeType = AgeGroup::Adult;
    }
    else
    {
        AgeType = AgeGroup::Child;
    }
}

void Passenger::PrintHumanInformation()
{
    // CLI_TRACE("\n\tNAME: {}\n\tSURNAME: {}\n\tDate Of Birth: {}\n\tAge: {}\n\tAge Group: {}\n\tBody Weight: {}\n\tLuggage Weight: {}\n\tCumulative Passenger Weight: {}", Name, Surname, DateOfBirth, Age, AgeGroupEnumToText(AgeType), BodyWeight, LuggageWeight, TotalWeight);
}

void Passenger::SetBodyWeight(double bodyWeight)
{
    TotalWeight -= BodyWeight;
    BodyWeight = bodyWeight;
    TotalWeight += BodyWeight;
}

void Passenger::SetLuggageWeight(double weight)
{
    TotalWeight -= LuggageWeight;
    LuggageWeight = weight;
    TotalWeight += LuggageWeight;
}

void Passenger::AddLuggageWeight(double weight)
{
    double oldWeight = LuggageWeight;
    LuggageWeight += weight;
    TotalWeight += weight;
}

void Passenger::RemoveLuggageWeight(double weight)
{
    double oldWeight = LuggageWeight;
    LuggageWeight -= weight;
    TotalWeight -= weight;
    if (LuggageWeight < 0)
    {
        LuggageWeight = 0;
    }
}