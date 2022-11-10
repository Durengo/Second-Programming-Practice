#include "Validation.h"
#include "durlib/PCH.h"
#include "Input.h"

#include "durlib/Log/Log.h"

namespace DURLIB
{
    // INPUT VALIDATION
    // RETURN -1 IF INPUT NOT VALID
    bool CanBeInt(const std::string &input)
    {
        if (isLetters(input) || Letters(input) > 0)
        {
            CLI_ERROR("{0} CONTAINS LETTERS WHEN CONVERTING TO INT", input);
            return false;
        }
        if (CountNegation(input) > 1)
        {
            CLI_ERROR("{0} CONTAINS TOO MANY NEGATION SYMBOLS", input);
            return false;
        }
        int converted;
        try
        {
            converted = std::stoi(input);
        }
        catch (std::invalid_argument &i)
        {
            CLI_ERROR("{0}", i.what());
            CLI_ERROR("EXCEPTION! NOT AN INTEGER NUMBER: {0}\nTry again:", input);
            return false;
        }
        catch (std::out_of_range &i)
        {
            CLI_ERROR("{0}", i.what());
            CLI_ERROR("EXCEPTION! INPUT OUT OF RANGE: {0}\nTry again:", input);
            return false;
        }

        return true;
    }

    int STOI(const std::string &input)
    {
        if (isLetters(input))
        {
            CLI_ERROR("{0} CONTAINS LETTERS WHEN CONVERTING TO INT", input);
            return -1;
        }
        int converted;
        try
        {
            converted = std::stoi(input);
        }
        catch (std::invalid_argument &i)
        {
            CLI_ERROR("{0}", i.what());
            CLI_ERROR("EXCEPTION! NOT AN INTEGER NUMBER: {0}\nTry again:", input);
            return -1;
        }
        catch (std::out_of_range &i)
        {
            CLI_ERROR("{0}", i.what());
            CLI_ERROR("EXCEPTION! INPUT OUT OF RANGE: {0}\nTry again:", input);
            return -1;
        }

        return converted;
    }

    int STOI(int min, int max, const std::string &input)
    {
        while (true)
        {
            int inputNew = STOI(input);
            if (inputNew >= min && inputNew <= max)
            {
                return inputNew;
            }
            else
            {
                CLI_ERROR("EXCEPTION! INPUT OUT OF RANGE: {0} in [MIN]{1}-[MAX]{2}\nTry again:", inputNew, min, max);
                return -1;
            }
        }
    }

    double DTOS(const std::string &input)
    {
        double converted;
        while (true)
        {
            try
            {
                converted = std::stod(input);
                break;
            }
            catch (std::invalid_argument &i)
            {
                CLI_ERROR("{0}", i.what());
                CLI_ERROR("EXCEPTION! NOT A DOUBLE NUMBER: {0}\nTry again:", input);
                return -1;
            }
            catch (std::out_of_range &i)
            {
                CLI_ERROR("{0}", i.what());
                CLI_ERROR("EXCEPTION! INPUT OUT OF RANGE: {0}\nTry again:", input);
                return -1;
            }
        }
        return converted;
    }

    std::string STOS(const std::string &input)
    {
        return input;
    }

    std::string STOS_CON(const std::string &input)
    {
        bool valid = false;
        do
        {
            valid = validateName(input);
            if (!valid)
            {
                CLI_ERROR("THIS DATA CANNOT HAVE:\n 1. MORE THAN ONE CAPITAL LETTER AND ONLY AT THE START;\n 2. ANY NUMBERS OR SYMBOLS;\n 3. WHITESPACE\nTry again: ");
                return "-1";
            }
        } while (!valid);
        return input;
    }

    std::string ITOS(int input)
    {
        std::string ss = std::to_string(input);
        return ss;
    }
}