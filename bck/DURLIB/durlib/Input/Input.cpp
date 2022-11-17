#include "Input.h"
#include "durlib/PCH.h"

#include "durlib/Log/Log.h"

namespace DURLIB
{
    int GIBI()
    {
        std::string input;
        int converted;
        while (true)
        {
            std::cin >> input;
            try
            {
                converted = std::stoi(input);
                break;
            }
            catch (std::invalid_argument &i)
            {
                CLI_ERROR("{0}", i.what());
                CLI_ERROR("EXCEPTION! NOT AN INTEGER NUMBER: {0}\nTry again:", input);
            }
            catch (std::out_of_range &i)
            {
                CLI_ERROR("{0}", i.what());
                CLI_ERROR("EXCEPTION! INPUT OUT OF RANGE: {0}\nTry again:", input);
            }
        }
        return converted;
    }

    int GIBI(int min, int max)
    {
        while (true)
        {
            int input = GIBI();
            if (input >= min && input <= max)
            {
                return input;
            }
            else
            {
                CLI_ERROR("EXCEPTION! INPUT OUT OF RANGE: {0} in [MIN]{1}-[MAX]{2}\nTry again:", input, min, max);
            }
        }
    }

    double GIBD()
    {
        std::string input;
        double converted;
        while (true)
        {
            std::cin >> input;
            try
            {
                converted = std::stod(input);
                break;
            }
            catch (std::invalid_argument &i)
            {
                CLI_ERROR("{0}", i.what());
                CLI_ERROR("EXCEPTION! NOT A DOUBLE NUMBER: {0}\nTry again:", input);
            }
            catch (std::out_of_range &i)
            {
                CLI_ERROR("{0}", i.what());
                CLI_ERROR("EXCEPTION! INPUT OUT OF RANGE: {0}\nTry again:", input);
            }
        }
        return converted;
    }

    std::string GIBS()
    {
        std::string input;
        std::cin >> input;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }

    std::string GIBS_NW()
    {
        std::string input;
        bool valid = false;
        do
        {
            std::getline(std::cin, input);
            valid = validateName(input);
            if (!valid)
            {
                CLI_ERROR("THIS DATA CANNOT HAVE:\n 1. MORE THAN ONE CAPITAL LETTER AND ONLY AT THE START;\n 2. ANY NUMBERS OR SYMBOLS;\n 3. WHITESPACE\nTry again: ");
            }
        } while (!valid);
        std::cin.clear();
        return input;
    }

    int Get_Input_Yes_Or_No()
    {
        while (true)
        {
            CLI_ERROR("Answer with: (1) Yes; (0) No.\n");
            int input = GIBI(0, 1);

            switch (input)
            {
            case 0:
                CLI_ERROR("\nNo selected!\n");
                return input;
            case 1:
                CLI_ERROR("\nYes selected!\n");
                return input;
            default:
                CLI_ERROR("\n!EXCEPTION!\n");
                break;
            }
        }
    }

    bool HasWhitespace(const std::string &text)
    {
        return all_of(text.begin(), text.end(), [](char ch)
                      { return (!isspace(ch)); });
    }

    bool validateName(const std::string &name)
    {
        if (name != "" && isLetters(name) && oneCapital(name))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isLetters(const std::string_view &text)
    {
        return all_of(text.begin(), text.end(), [](char ch)
                      { return (isalpha(ch)); });
    }

    int Letters(const std::string &text)
    {
        int count = 0;
        for(int i = 0; i < text.size(); i++)
        {
            if(isalpha(text[i]))
            {
                count++;
            }
        }
        return count;
    }

    bool isNumbers(const std::string_view &text)
    {
        return all_of(text.begin(), text.end(), [](char ch)
                      { return (isdigit(ch)); });
    }

    int Numbers(const std::string &text)
    {
        int count = 0;
        for(int i = 0; i < text.size(); i++)
        {
            if(isdigit(text[i]))
            {
                count++;
            }
        }
        return count;
    }

    // int Symbols(const std::string &text)
    // {
    //     int count = 0;
    //     for(int i = 0; i < text.size(); i++)
    //     {
    //         if(iss(text[i]))
    //         {
    //             count++;
    //         }
    //     }
    //     return count;
    // }

    int CountNegation(const std::string &text)
    {
        int count = 0;
        for(int i = 0; i < text.size(); i++)
        {
            if(text[i] == '-')
            {
                count++;
            }
        }
        return count;
    }

    bool hasNegation(const std::string_view &text)
    {
        return all_of(text.begin(), text.end(), [](char ch)
                        { return (ch == '-'); });
    }

    bool oneCapital(const std::string &text)
    {
        int cCount = 0;
        for (std::size_t i{}; i < text.length() && cCount < text.length(); i++)
        {
            // CLI_ERROR("NAME[{0}] = {1}; UPPER[{0}] = {2}\n", i, name[i], toupper(name.c_str()[i]));
            switch (cCount)
            {
            case 0:
                if (text[0] != toupper(text.c_str()[0]))
                {
                    CLI_ERROR("FIRST LETTER IS NOT CAPITAL.\n");
                    return false;
                }
                cCount++;
                break;
            default:
                if (text[i] == toupper(text.c_str()[i]))
                {
                    CLI_ERROR("MORE THAN ONE CAPITAL LETTER.\n");
                    return false;
                }
                cCount++;
                break;
            }
        }
        return true;
    }
}