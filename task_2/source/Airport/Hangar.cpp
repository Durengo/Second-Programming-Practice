#include "Hangar.h"

#include "durlib/Log/Log.h"

Hangar::Hangar()
    : UniquePlaneID(0), HangarSize(0)
{
}

Hangar::~Hangar()
{
}

void Hangar::AddPlane(AirplaneType type)
{
    Airplane *NewPlane = new Airplane(UniquePlaneID, type);
    Airplanes.push_back(NewPlane);
    UniquePlaneID++;
    HangarSize++;
    // NewPlane->PrintAirplaneInformation();
}

void Hangar::RemovePlaneByID(int planeID)
{
    Airplanes.erase(std::remove_if(Airplanes.begin(), Airplanes.end(), [&](Airplane *item)
                                   { return item->GetID() == planeID; }));
}

void Hangar::RemovePlaneByIndex(int index)
{
    if (index < 0 || index > Airplanes.size())
    {
        CLI_ASSERT(0, "INVALID INDEX.");
    }
    int count = 0;
    for (auto i = Airplanes.begin(); i != Airplanes.end(); i++)
    {
        if (count == index)
        {
            Airplanes.erase(i);
        }
        count++;
    }
}

Airplane *Hangar::GetPlane(size_t index)
{
    if (index < 0 || index > Airplanes.size())
    {
        CLI_ASSERT(0, "INVALID INDEX.");
    }
    return Airplanes[index];
}

void Hangar::PrintAllPlanesInHangar()
{
    CLI_TRACE("PRINTING ALL PLANES IN CURRENT HANGAR:");
    for (int i = 0; i < Airplanes.size(); i++)
    {
        CLI_INFO("Plane {} - {}", i + 1, Airplanes[i]->GetTypeAsString());
    }
}