#pragma once

#include <string>

// std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

namespace DURLIB
{
    // INPUT STREAM
    int GIBI();
    int GIBI(int min, int max);
    double GIBD();
    std::string GIBS();
    std::string GIBS_NW();
    int Get_Input_Yes_Or_No();
    bool HasWhitespace(const std::string &text);
    bool validateName(const std::string &name);
    bool isLetters(const std::string_view &text);
    bool isNumbers(const std::string_view &text);
    bool oneCapital(const std::string &text);
}