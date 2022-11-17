#pragma once

#include <string>

#include "Hangar.h"
#include "Lobby.h"

// Not currently used properly. But if extended could provide hard cap limits for the size of lobbies and hangars.
enum AirportSizeType
{
    None = 0,
    LargeAirport = 1,
    MediumAirport = 2,
    SmallAirport = 3,
};

// A struct that holds the latitude, longitude, country, and city information of the airport.
// Latitude and longitude are extremely important for the calculation of distance for flights.
struct AirportLocation
{
    double Latitude;
    double Longitude;
    std::string Country;
    std::string City;
};

// The airport class is the amalgamation of both the Airplane class and the Passenger class.
// The airport class is an indirect abstraction layer for both of those classes.
class Airport : public Hangar, public Lobby
{
private:
    // Name of the airport
    std::string Name;
    // ISO ID of the airport.
    std::string Ident;
    // Size of the airport.
    AirportSizeType Size;
    // Location of the airport.
    AirportLocation Location;

public:
    Airport(const std::string &name, const std::string &ident, const AirportLocation &location);
    Airport(const std::string &name, const std::string &ident, const AirportSizeType &size, const AirportLocation &location);
    ~Airport();

    // LOBBY INHERITANCE OVERRIDE
    void AddPerson(Passenger *passenger) override;
    // HANGAR INHERITANCE OVERRIDE
    void AddPlane(AirplaneType type) override;

    void PrintAllPlanesInHangar() override;

    // GETTERS:
    std::string GetAirportName() const { return Name; }

    std::string GetAirportIdent() const { return Ident; }

    AirportSizeType GetAirportSizeType() const { return Size; }

    AirportLocation GetAirportLocation() const { return Location; }
};