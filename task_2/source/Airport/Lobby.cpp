#include "Lobby.h"

#include "durlib/Log/Log.h"

Lobby::Lobby()
    : LobbySize(0)
{
}

Lobby::~Lobby()
{
}

void Lobby::AddPerson(Passenger *passenger)
{
    Passengers.push_back(passenger);
    LobbySize++;
    // passenger->PrintHumanInformation();
}

void Lobby::RemovePersonByIndex(int index)
{
    if (index < 0 || index > Passengers.size())
    {
        CLI_ASSERT(0, "INVALID INDEX.");
    }
    int count = 0;
    for (auto i = Passengers.begin(); i != Passengers.end(); i++)
    {
        if (count == index)
        {
            Passengers.erase(i);
        }
        count++;
    }
}

Passenger *Lobby::GetPassenger(size_t index)
{
    if (index < 0 || index > Passengers.size())
    {
        CLI_ASSERT(0, "INVALID INDEX.");
    }
    return Passengers[index];
}