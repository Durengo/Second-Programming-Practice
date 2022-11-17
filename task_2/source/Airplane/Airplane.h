#pragma once

#include <string>

#include "Flight.h"

class Passenger;

// Airplane types that are somewhat based on real-life example planes.
enum AirplaneType
{
    // Based on Phenom 300E
    LIGHT_JET = 0,
    // Based on Cessna Citation X
    MID_SIZE_JET = 1,
    // Based on Boeing 747-8
    JUMBO_JET = 2
};

const char *AirplaneTypeEnumToText(AirplaneType type);

class Airplane : public Flight
{
private:
    // Currently these values are not of much use.
    // Name of airplane.
    std::string Name;
    // ID of the airplane.
    uint64_t ID;

protected:
    // Get type of airplane.
    AirplaneType Type;
    // KILOMETERS
    int MaxRange = 0;
    // KILOGRAMS
    double BaseWeight = 0;
    double CurrentWeight = 0;
    // LITERS
    double MaxFuel = 0;
    double CurrentFuel = 0;
    // PERSONS
    int MaxPassengers = 0;
    int CurrentPassengers = 0;
    // KILOMETERS / HOUR
    double MaxSpeed = 0;
    // LITRES / HOUR
    double AverageFuelConsumption = 0;

public:
    Airplane(uint64_t id);
    Airplane(uint64_t id, AirplaneType type);
    Airplane(std::string name, uint64_t id);
    ~Airplane();

    // Begin flight.
    void Fly();

    void PrintAirplaneInformation();

    // Add fuel to the airplane.
    void AddFuel(double amount);
    // void RemoveFuel(double amount);
    // Add a passenger to the airplane.
    void AddPassenger(Passenger *passenger);

    // GETTERS:
    std::string GetName() const { return Name; }

    uint64_t GetID() const { return ID; }

    std::string GetTypeAsString() const { return AirplaneTypeEnumToText(Type); }

    int GetMaxRange() const { return MaxRange; }

    double GetBaseWeight() const { return BaseWeight; }
    double GetCurrentWeight() const { return CurrentWeight; }

    double GetMaxFuel() const { return MaxFuel; }
    double GetCurrentFuel() const { return CurrentFuel; }

    int GetMaxPassengers() const { return MaxPassengers; }
    int GetCurrentPassengers() const { return CurrentPassengers; }

    double GetMaxSpeed() const { return MaxSpeed; }

    double GetAverageFuelConsumption() const { return AverageFuelConsumption; }

private:
    // Used in the constructor to identify which AirplaneType has been passed and sets the appropriate variables with a switch statement.
    void CheckPlaneType();
};