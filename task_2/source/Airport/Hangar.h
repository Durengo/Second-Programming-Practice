#pragma once

#include "Airplane/Airplane.h"

#include <vector>

// A collection of planes for the airport class (generalization layer).

class Hangar
{
protected:
    // List of airplanes
    std::vector<Airplane *> Airplanes;
    uint64_t UniquePlaneID;
    int HangarSize;

public:
    Hangar();
    ~Hangar();

    virtual void PrintAllPlanesInHangar();

    // Add/remove a plane to the airport
    virtual void AddPlane(AirplaneType type);
    void RemovePlaneByID(int planeID);
    void RemovePlaneByIndex(int index);

    // GETTERS:
    Airplane *GetPlane(size_t index);

    int GetHangarSize() const { return HangarSize; }

private:
    void SetVariables();
};