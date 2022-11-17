#pragma once

// This class is created with the singleton method.
// This class is a mini simulation and a showcase of all the classes within this project.
// Firstly, the class generates airport objects from the Airport class.
// Secondly, the class generates passenger objects from the Passenger class.
// Thirdly, the class generates plane objects from the Airplane class.
// Fourthly, the class assigns passenger objects to the plane objects.
// Lastly, the class executes the "fly()"" methods.

// The passenger and airport objects are implemented using CSV parsing.
// Two files are provided in the "data" folder that stores the necessary .csv files.
// Removing the files will crash the program!

// For passengers variables like "BodyWeight" and "LuggageWeight" are randomized.
// For planes the add fuel variable is randomized.
// By randomizing these variables, the planes can fail within the "fly()"" method,
// by being overweight and the fuel consumption going up or not having enough fuel.

// Randomization factors are based on the chaos formula which adds an unpredictability factor that the user can modify.

#include "Airport/Airport.h"

#include "csv.h"

#include <vector>
#include <string>

// Hardcap .csv file object amounts.
static const int AirportAmount = 10;
static const int PassengerAmount = 1000;

// Can be modified at will.
static const int MaximumPlanes = AirportAmount + 50;

// Plane tracker.
static unsigned int PlaneCounter = 0;

// Chaos formula variables.
static double CHAOS_PERCENTAGE = 0.5;
static int CHAOS_RATE = 1000;
static double CHAOS_FACTOR = CHAOS_PERCENTAGE * (double)CHAOS_RATE;

// Used for debugging. But can be set up to -1000 to generate 1 person per every airport. Can also be set to any value that is not lower than -1000 or higher than -1.
static const int DEBUG_MAX_PEOPLE = -0;

// Used for string concatenation when generation airport names.
static const std::string InternationalAirport = "International Airport";

// .csv File paths. DO NOT MODIFY WITHOUT MOVING THE FILES TO THE APPROPRIATE PATHS!
static const std::string AirportsCSVFilepath = "data/csv/airports.csv";
static const std::string PassengersCSVFilepath = "data/csv/passengers.csv";

class AirportSimulation
{
private:
    // List of airport and passenger objects.
    static std::vector<Airport> s_Airports;
    static std::vector<Passenger *> s_Passengers;
    // CSV PARSER
    static io::CSVReader<5> *Airports_CSV;
    static io::CSVReader<3> *Passengers_CSV;
    // SINGLETON
    static AirportSimulation *Instance;
    AirportSimulation();
    // bool for how much information should be displayed.
    static bool Verbose;

public:
    ~AirportSimulation();

    // '*' - are optional methods.
    // Run these methods in main by such order: Init(), *SetChaosPercentage(), *SetChaosRate(), *SetVerbose(), Execute(), Destroy()
    static void Init();
    static void Execute();
    static void Destroy();
    static void SetChaosPercentage(double percentage);
    static void SetChaosRate(int rate) { CHAOS_RATE = rate; }
    static void SetVerbose(char verbose);

private:
    static void CalculateChaosFactor();
    static void GenerateAirports();
    static void GeneratePassengers();
    static void GeneratePlanes();
    static void AssignPassengersToAirports();
    static void PrintInformation();
};