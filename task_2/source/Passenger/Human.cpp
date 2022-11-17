#include "Human.h"

#include <durlib/Log/Log.h>

Human::Human(const std::string &name, const std::string &surname, const DURLIB::DateMath::DateYMD &birthday, double bodyWeight)
    : Name(name), Surname(surname), DateOfBirth(birthday), BodyWeight(bodyWeight)
{
    Age = DURLIB::DateMath::CalculateYears(DateOfBirth);
}

Human::Human(const std::string &name, const std::string &surname, const DURLIB::DateMath::DateYMD &birthday)
    : Name(name), Surname(surname), DateOfBirth(birthday), BodyWeight(0)
{
    Age = DURLIB::DateMath::CalculateYears(DateOfBirth);
}

Human::~Human()
{
}

void Human::PrintHumanInformation()
{
    CLI_TRACE("\n\tNAME: {}\n\tSURNAME: {}\n\tDate Of Birth: {}\n\tAge: {}\n\tBody Weight: {}", Name, Surname, DateOfBirth, Age, BodyWeight);
}