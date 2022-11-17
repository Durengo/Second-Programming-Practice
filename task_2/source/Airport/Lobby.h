#pragma once

#include "Passenger/Passenger.h"

// A collection of passengers for the airport class (generalization layer).

class Lobby
{
protected:
    // List of passengers
    std::vector<Passenger *> Passengers;
    int LobbySize;

public:
    Lobby();
    ~Lobby();

    // Add/remove a person to the airport.
    virtual void AddPerson(Passenger *passenger);
    void RemovePersonByIndex(int index);

    // GETTERS:
    Passenger *GetPassenger(size_t index);

    int GetLobbySize() const { return LobbySize; }
};