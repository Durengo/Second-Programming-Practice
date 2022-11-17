#pragma once

class Airport;

// This class holds the calculation methods for planes to find out the distance, travel time, and fuel consumption between airports.

class Flight
{
protected:
    // Kilometers
    double Distance = 0;
    // Hours
    double TravelTime = 0;
    // Liters
    double FuelConsumed = 0;

    bool Calculated = false;

private:
    // To calculate the distance, travel time, and fuel consumption we need to assign two airport objects.
    Airport *A;
    Airport *B;

public:
    Flight();
    ~Flight();

    // Add airports methods:
    void SetAirports(Airport *a, Airport *b)
    {
        A = a;
        B = b;
    }
    void SetAirportA(Airport *a) { A = a; }
    void SetAirportB(Airport *b) { B = b; }

    // Calculates distance, travel time, and fuel consumption. Requires plane speed and average consumption values.
    void CalculateFlight(double speed, double average_fuel_consumption_per_hour);

    // Prints basic flight information.
    void PrintFlightInformation();

    double GetDistance() const { return Distance; }

    double GetTravelTime() const { return TravelTime; }

    double GetFuelConsumed() const { return FuelConsumed; }

    Airport *GetAirportA() const { return A; }
    Airport *GetAirportB() const { return B; }

protected:
    // Separate private functions for calculating each variable.
    void CalculateDistance();
    void CalculateTime(double speed);
    void CalculateFuel(double speed, double average_fuel_consumption_per_hour);
};