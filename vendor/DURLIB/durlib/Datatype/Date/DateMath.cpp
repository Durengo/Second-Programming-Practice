#include "DateMath.h"

#include <time.h>

namespace DURLIB
{
    namespace DateMath
    {
        int MonthDays[12] =
            {
                31, // January
                28, // February - NON LEAP YEAR
                31, // March
                30, // April
                31, // May
                30, // June
                31, // July
                31, // August
                30, // September
                31, // October
                30, // November
                31  // December
        };
        const char *monthsEnumToText(Months month)
        {
            switch (month)
            {
            case Months::January:
                return "January";
                break;
            case Months::February:
                return "February";
                break;
            case Months::March:
                return "March";
                break;
            case Months::April:
                return "April";
                break;
            case Months::May:
                return "May";
                break;
            case Months::June:
                return "June";
                break;
            case Months::July:
                return "July";
                break;
            case Months::August:
                return "August";
                break;
            case Months::September:
                return "September";
                break;
            case Months::October:
                return "October";
                break;
            case Months::November:
                return "November";
                break;
            case Months::December:
                return "December";
                break;
            default:
                CLI_ASSERT(0, "DATE MATH LOGIC OUT OF BOUNDS.")
                return "-1";
            }
        }

        int getMaxYear()
        {
            // NEW
            struct std::tm localTime;
            time_t now = std::time(nullptr);
            localtime_s(&localTime, &now);
            return 1900 + localTime.tm_year;
            // OLD WITH MSVC WARNING:
            // std::time_t t = std::time(nullptr);
            // std::tm *const localTime = std::localtime(&t);
            // return 1900 + localTime->tm_year;
        }

        int getMaxMonth()
        {
            // NEW
            struct std::tm localTime;
            time_t now = std::time(nullptr);
            localtime_s(&localTime, &now);
            return localTime.tm_mon + 1;
            // OLD WITH MSVC WARNING:
            // std::time_t t = std::time(nullptr);
            // std::tm *const localTime = std::localtime(&t);
            // return (localTime->tm_mon + 1);
        }

        int getMaxDay()
        {
            // NEW
            struct std::tm localTime;
            time_t now = std::time(nullptr);
            localtime_s(&localTime, &now);
            return localTime.tm_mday;
            // OLD WITH MSVC WARNING:
            // std::time_t t = std::time(nullptr);
            // std::tm *const localTime = std::localtime(&t);
            // return localTime->tm_mday;
        }

        bool isLeapYear(int year)
        {
            return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
        }

        int CalculateYears(DateYMD Date)
        {
            // NEW
            struct std::tm localTime;
            time_t now = std::time(nullptr);
            localtime_s(&localTime, &now);
            int day = localTime.tm_mday - Date.Day;
            int month = (localTime.tm_mon + 1) - Date.Month;
            int year = (1900 + localTime.tm_year) - Date.Year;
            // OLD WITH MSVC WARNING:
            // std::time_t t = std::time(nullptr);
            // std::tm *const localTime = std::localtime(&t);
            // int day = localTime->tm_mday - Date.Day;
            // int month = (localTime->tm_mon + 1) - Date.Month;
            // int year = (1900 + localTime->tm_year) - Date.Year;

            if (day < 0)
            {
                month = month - 1;
            }
            if (month < 0)
            {
                year = year - 1;
            }

            return year;
        }

        int DaysUntilDate(DateYMD Date)
        {
            // NEW
            struct std::tm localTime;
            time_t now = std::time(nullptr);
            localtime_s(&localTime, &now);
            int totalDays = 0;
            int year = 1900 + localTime.tm_year;
            bool isLeap = isLeapYear(year);
            // OLD WITH MSVC WARNING:
            // std::time_t t = std::time(nullptr);
            // std::tm *const localTime = std::localtime(&t);
            // int totalDays = 0;
            // int year = 1900 + localTime->tm_year;
            // bool isLeap = isLeapYear(year);
            // ALL localTime-> have been changed to localTime. <-----!!!

            // If date is on the same month of the same day then return 0
            if (Date.Month == localTime.tm_mon && Date.Day == localTime.tm_mday)
            {
                return totalDays;
            }
            // If date is on the same month but greater than current day return [date day - current day]
            if (Date.Month == localTime.tm_mon && Date.Day > localTime.tm_mday)
            {
                totalDays = Date.Day - localTime.tm_mday;
                return totalDays;
            }
            // If date is on the same month but less than the current day return [~1 year + days]
            if (Date.Month == localTime.tm_mon && Date.Day < localTime.tm_mday)
            {
                int icount = 0;
                for (int i = localTime.tm_mon; icount != 12; i++)
                {
                    if (i == 12)
                    {
                        i = 0;
                        year++;
                        isLeap = isLeapYear(year);
                    }
                    if (i == 1)
                    {
                        if (isLeap)
                            totalDays++;
                    }
                    totalDays += MonthDays[i];
                    icount++;
                }
                totalDays += Date.Day - localTime.tm_mday;
                return totalDays;
            }
            // If date is more than the current month return [12-current month + days]
            if (Date.Month > localTime.tm_mon)
            {
                if (static_cast<Months>(localTime.tm_mon) == Months::February)
                {
                    if (isLeap)
                        totalDays++;
                }
                totalDays += MonthDays[(int)localTime.tm_mon] - localTime.tm_mday;
                int icount = 0;
                for (int i = localTime.tm_mon + 1; i != Date.Month; i++)
                {
                    if (i == 12)
                    {
                        i = 0;
                        year++;
                        isLeap = isLeapYear(year);
                    }
                    if (i == Months::February)
                    {
                        if (isLeap)
                            totalDays++;
                    }
                    totalDays += MonthDays[i];
                    icount++;
                }
                totalDays += Date.Day;
                return totalDays;
            }
            // If date is less than the current month return [~1 year + days]
            if (Date.Month < localTime.tm_mon)
            {
                if (static_cast<Months>(localTime.tm_mon) == Months::February)
                {
                    if (isLeap)
                        totalDays++;
                }
                totalDays += MonthDays[(int)localTime.tm_mon] - localTime.tm_mday;
                for (int i = localTime.tm_mon + 1; i != 12; i++)
                {
                    if (i == Months::February)
                    {
                        if (isLeap)
                            totalDays++;
                    }
                    totalDays += MonthDays[i];
                }
                int icount = 0;
                for (int i = 0; icount != Date.Month; i++)
                {
                    if (i == 12)
                    {
                        i = 0;
                        year++;
                        isLeap = isLeapYear(year);
                    }
                    if (i == Months::February)
                    {
                        if (isLeap)
                            totalDays++;
                    }
                    totalDays += MonthDays[i];
                    icount++;
                }
                totalDays += Date.Day;
                return totalDays;
            }
            CLI_ASSERT(0, "OUT OF BOUNDS.");
            return -1;
        }
    }
}