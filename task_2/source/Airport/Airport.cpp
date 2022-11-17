#include "Airport.h"

#include <durlib.h>

Airport::Airport(const std::string &name, const std::string &ident, const AirportLocation &location)
    : Name(name), Ident(ident), Size(AirportSizeType::None), Location(location)
{
    DEBUG_TRACE("AIRPORT CREATED: {} COORDINATES: LAT = {}; LON = {}", name, location.Latitude, location.Longitude);
}

Airport::Airport(const std::string &name, const std::string &ident, const AirportSizeType &size, const AirportLocation &location)
    : Name(name), Ident(ident), Size(size), Location(location)
{
    DEBUG_TRACE("AIRPORT CREATED: {} COORDINATES: LAT = {}; LON = {}", name, location.Latitude, location.Longitude);
}

Airport::~Airport()
{
}

void Airport::PrintAllPlanesInHangar()
{
    CLI_TRACE("PRINTING ALL PLANES IN {} HANGAR:", Name);
    for (int i = 0; i < Airplanes.size(); i++)
    {
        CLI_INFO("Plane {} - {}", i + 1, Airplanes[i]->GetTypeAsString());
    }
}

void Airport::AddPlane(AirplaneType type)
{
    Airplane *NewPlane = new Airplane(UniquePlaneID, type);
    Airplanes.push_back(NewPlane);
    UniquePlaneID++;
    HangarSize++;
    // DEBUG_TRACE("NEW PLANE ADDED FOR {}, TYPE: {}", Name, AirplaneTypeEnumToText(type));
}

void Airport::AddPerson(Passenger *passenger)
{
    Passengers.push_back(passenger);
    LobbySize++;
    // DEBUG_TRACE("NEW PERSON ADDED FOR {}, NAME: {}", Name, passenger->GetName());
}