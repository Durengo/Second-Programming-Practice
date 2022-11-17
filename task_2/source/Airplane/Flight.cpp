#include "Flight.h"

#include <durlib.h>

#include "Airport/Airport.h"

Flight::Flight()
    : Distance(0), A(nullptr), B(nullptr)
{
}

Flight::~Flight()
{
}

// Using the spherical law of cosines formula we can find the distance between two points on Earth.
// This formula requires two sets of coordinates: the latitude and the longitude of the first and second position.
// Each airport object has latitude and longitude positions.
// The formula returns the distance in meters, hence we turn it into kilometers (/= 1000).
void Flight::CalculateDistance()
{
    if (A != nullptr && B != nullptr)
    {
        double aLat = A->GetAirportLocation().Latitude;
        double aLon = A->GetAirportLocation().Longitude;
        double bLat = B->GetAirportLocation().Latitude;
        double bLon = B->GetAirportLocation().Longitude;
        Distance = DURLIB::Spherical_Law_Of_Cosines({aLat, aLon}, {bLat, bLon});
        Distance /= 1000;
    }
}

void Flight::CalculateTime(double speed)
{
    TravelTime = (Distance / 1000) / speed;
}
void Flight::CalculateFuel(double speed, double average_fuel_consumption_per_hour)
{
    FuelConsumed = average_fuel_consumption_per_hour * TravelTime;
}

void Flight::CalculateFlight(double speed, double average_fuel_consumption_per_hour)
{
    if (Calculated)
    {
        return;
    }
    CalculateDistance();
    CalculateTime(speed);
    CalculateFuel(speed, average_fuel_consumption_per_hour);
    // DEBUG_FATAL("COORDINATES: {} {} | {} {}", A->GetAirportLocation().Latitude, A->GetAirportLocation().Longitude, B->GetAirportLocation().Latitude, B->GetAirportLocation().Longitude);
    // DEBUG_FATAL("DISTANCE = {}", Distance);
    // DEBUG_FATAL("TRAVEL TIME = {}", TravelTime);
    // DEBUG_FATAL("CONSUMED FUEL = {}", FuelConsumed);
    Calculated = true;
}

void Flight::PrintFlightInformation()
{
    CLI_TRACE("\t{} -----------> {};\n\t\t\tDistance Between Airports: {} km;\n\t\t\tTime To Fly From A To B: {} hours;\n\t\t\tAmount Of Fuel That Will Be Consumed: {} litres",
              A->GetAirportName(), B->GetAirportName(),
              Distance, TravelTime, Distance);
}