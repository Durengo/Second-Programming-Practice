#pragma once

// This class will be used with the human class. It is a very simple implementation of any additional luggage a person might take with the to the flight.
// Again, the luggage weight will be used when calculating the fuel cost for flights.

class Luggage
{
protected:
    double LuggageWeight;

public:
    Luggage();
    Luggage(double luggageWeight);
    ~Luggage();

    // GETTERS & SETTERS:
    double GetLuggageWeight() const { return LuggageWeight; }

    // Leaving these methods pure virtual because it is easier to implement once.
    virtual void SetLuggageWeight(double weight) = 0;
    virtual void AddLuggageWeight(double weight) = 0;
    virtual void RemoveLuggageWeight(double weight) = 0;
};