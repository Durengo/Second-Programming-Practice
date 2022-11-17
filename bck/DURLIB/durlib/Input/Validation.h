#pragma once

#include <string>

namespace DURLIB
{
    // INPUT VALIDATION
    bool CanBeInt(const std::string &input);
    int STOI(const std::string &input);
    int STOI(int min, int max, const std::string &input);
    double DTOS(const std::string &input);
    std::string STOS(const std::string &input);
    std::string STOS_CON(const std::string &input);
    std::string ITOS(int input);
}