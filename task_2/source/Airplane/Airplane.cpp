#include "Airplane.h"

#include <durlib.h>

#include "Passenger/Passenger.h"

const char *AirplaneTypeEnumToText(AirplaneType type)
{
    switch (type)
    {
    case AirplaneType::LIGHT_JET:
        return "Light Jet";
        break;
    case AirplaneType::MID_SIZE_JET:
        return "Mid-Size Jet";
        break;
    case AirplaneType::JUMBO_JET:
        return "Jumbo Jet";
        break;
    default:
        CLI_ASSERT(0, "AGE GROUP ENUM LOGIC OUT OF BOUNDS.")
        return "-1";
    }
}

Airplane::Airplane(uint64_t id)
    : Name("NO NAME SET"), ID(id)
{
}

Airplane::Airplane(uint64_t id, AirplaneType type)
    : Name("NO NAME SET"), ID(id), Type(type)
{
    CheckPlaneType();
}

Airplane::Airplane(std::string name, uint64_t id)
    : Name(name), ID(id)
{
}

Airplane::~Airplane()
{
}

void Airplane::CheckPlaneType()
{
    switch (Type)
    {
    case AirplaneType::LIGHT_JET:
        MaxRange = 3723;
        BaseWeight = 5253;
        MaxFuel = 2428;
        MaxPassengers = 9;
        MaxSpeed = 838;
        AverageFuelConsumption = 567;
        CurrentWeight += BaseWeight;
        break;
    case AirplaneType::MID_SIZE_JET:
        MaxRange = 5926;
        BaseWeight = 10038;
        MaxFuel = 5897;
        MaxPassengers = 9;
        MaxSpeed = 959;
        AverageFuelConsumption = 1527;
        CurrentWeight += BaseWeight;
        break;
    case AirplaneType::JUMBO_JET:
        MaxRange = 14430;
        BaseWeight = 190000;
        MaxFuel = 243400;
        MaxPassengers = 660;
        MaxSpeed = 920;
        AverageFuelConsumption = 10230;
        CurrentWeight += BaseWeight;
        break;
    default:
        CLI_ASSERT(0, "AIRPLANE TYPE ENUM LOGIC OUT OF BOUNDS.")
        break;
    }
}

void Airplane::Fly()
{
    // Calculate distance, time taken, and fuel consumption between airports.
    CalculateFlight(MaxSpeed, AverageFuelConsumption);
    // If the distance between the airports exceed the maximum limit the plane can fly, then the plane won't even attempt to fly.
    if (Distance > MaxRange)
    {
        CLI_ERROR("FLIGHT FAILED! DISTANCE IS TOO GREAT. PLANE'S MAX RANGE IS {} km, distance between airports is {} km", MaxRange, std::floor(Distance));
        Distance = 0;
        return;
    }
    // If the fuel consumed for the flight is greater than the current fuel the plane will crash.
    if (FuelConsumed > CurrentFuel)
    {
        CLI_ERROR("FLIGHT FAILED! NOT ENOUGH FUEL. Plane has crashed.");
        Distance = 0;
        TravelTime = 0;
        FuelConsumed = 0;
        return;
    }
    // If everything is ok the plane will fly to the other airport and land safely.
    CLI_INFO("FLIGHT SUCCESSFUL!");
}

void Airplane::PrintAirplaneInformation()
{
    CLI_TRACE("\tType: {};\n\t\t\tBase Weight (empty): {} / Current Weight (people, luggage, fuel): {};\n\t\t\tCurrent Fuel: {} / Max Fuel: {};\n\t\t\tMax Range: {};\n\t\t\tCurrent Passengers: {} / Max Passengers: {};\n\t\t\tMax Speed: {};\n\t\t\tAverage Fuel Consumption (l/h): {}",
              GetTypeAsString(), BaseWeight, CurrentWeight,
              CurrentFuel, MaxFuel, MaxRange,
              CurrentPassengers, MaxPassengers,
              MaxSpeed, AverageFuelConsumption);
}

void Airplane::AddFuel(double amount)
{
    // TODO: unsigned double implementation?
    if (amount < 0)
    {
        CLI_TRACE("Attempting to add negative amount, will convert to absolute.");
    }
    else if (std::abs(amount) > MaxFuel && CurrentFuel < MaxFuel)
    {
        CurrentFuel = MaxFuel;
        CurrentWeight += MaxFuel - CurrentFuel;
        AverageFuelConsumption += (MaxFuel - CurrentFuel) * 0.8;
    }
    else if (CurrentFuel >= MaxFuel || CurrentFuel + std::abs(amount) > MaxFuel)
    {
        CLI_ERROR("Cannot store fuel amount! Current = {}; Max = {}; Trying to add {} units", CurrentFuel, MaxFuel, amount);
        return;
    }
    else
    {
        double oldAmount = CurrentFuel;
        double oldPlaneWeight = CurrentWeight;
        CurrentFuel += std::abs(amount);
        CurrentWeight += std::abs(amount);
        AverageFuelConsumption += std::abs(amount) * 0.8;
        DEBUG_WARN("ADDED {} FUEL; OLD: {}, CURRENT: {}, MAX: {} | Previous plane weight: {}, new: {}",
                   std::abs(amount), oldAmount, CurrentFuel, MaxFuel, oldPlaneWeight, CurrentWeight);
    }
}

void Airplane::AddPassenger(Passenger *passenger)
{
    double tempWeight = passenger->GetTotalWeight();
    AverageFuelConsumption += tempWeight * 0.5;
    CurrentWeight += tempWeight;
    CurrentPassengers++;
}

// void Airplane::RemoveFuel(double amount)
// {
//     if (amount == 0)
//     {
//         return;
//     }
//     else if (amount < 0)
//     {
//         CLI_TRACE("Attempting to add negative amount, will convert to absolute.");
//     }
//     else if (std::abs(amount) > MaxFuel || CurrentFuel + std::abs(amount) * -1 < 0 || std::abs(amount) > CurrentFuel)
//     {
//         CLI_ERROR("Cannot remove more cargo than maximum or current! Current = {}; Max = {}; Trying to remove {} units", CurrentFuel, MaxFuel, amount);
//         return;
//     }
//     else
//     {
//         double oldAmount = CurrentFuel;
//         double oldPlaneWeight = CurrentWeight;
//         CurrentFuel += std::abs(amount) * -1;
//         CurrentWeight += std::abs(amount) * -1;
//         // CLI_WARN("REMOVED {} FUEL; OLD: {}, CURRENT: {}, MAX: {} | Previous plane weight: {}, new: {}",
//         //          std::abs(amount), oldAmount, CurrentFuel, MaxFuel, oldPlaneWeight, CurrentWeight);
//     }
// }
