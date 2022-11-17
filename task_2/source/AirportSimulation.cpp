#include "AirportSimulation.h"

#include <durlib/Log/Log.h>
#include <durlib/Input/Validation.h>

AirportSimulation *AirportSimulation::Instance = nullptr;

std::vector<Airport> AirportSimulation::s_Airports;
std::vector<Passenger *> AirportSimulation::s_Passengers;

io::CSVReader<5> *AirportSimulation::Airports_CSV = nullptr;
io::CSVReader<3> *AirportSimulation::Passengers_CSV = nullptr;

bool AirportSimulation::Verbose = true;

AirportSimulation::AirportSimulation()
{
    CLI_FATAL("Airport Simulation Started.");
}
AirportSimulation::~AirportSimulation()
{
    if (Instance != nullptr)
    {
        AirportSimulation *temp = Instance;
        Instance = nullptr;
        delete (temp);
    }
    CLI_FATAL("Airport Simulation Stopped.");
}
void AirportSimulation::Init()
{
    if (Instance == nullptr)
    {
        Instance = new AirportSimulation();
    }
}
void AirportSimulation::Destroy()
{
    AirportSimulation *temp = Instance;
    Instance = nullptr;
    delete (temp);
    s_Airports.clear();
    s_Passengers.clear();
    io::CSVReader<5> *tempCSV1 = Airports_CSV;
    Airports_CSV = nullptr;
    delete (tempCSV1);
    io::CSVReader<3> *tempCSV2 = Passengers_CSV;
    Passengers_CSV = nullptr;
    delete (Passengers_CSV);
    PlaneCounter = 0;
    Verbose = true;
}

void AirportSimulation::SetChaosPercentage(double percentage)
{
    if (percentage < 0 || percentage > 1)
    {
        CLI_ERROR("Chaos factor must be in a decimal (percentage) form. >= 0 or <= 1. Entered amount: {}", percentage);
    }
    else
    {
        CHAOS_PERCENTAGE = percentage;
    }
}
void AirportSimulation::CalculateChaosFactor()
{
    CHAOS_FACTOR = CHAOS_PERCENTAGE * (double)CHAOS_RATE;
}
void AirportSimulation::SetVerbose(char verbose)
{
    switch (verbose)
    {
    case 'y':
        Verbose = true;
        return;
    case 'n':
        Verbose = false;
        return;
    default:
        CLI_ERROR("Char is not defined. Leaving verbose ON.");
        return;
    }
}

void AirportSimulation::GenerateAirports()
{
    std::ifstream file(AirportsCSVFilepath);
    if (!file.is_open())
    {
        system("dir");
        DEBUG_ASSERT(0, "COULD NOT OPEN FILE.");
    }
    Airports_CSV = new io::CSVReader<5>(AirportsCSVFilepath);
    Airports_CSV->read_header(io::ignore_extra_column, "city", "airport", "latitude", "longitude", "country");
    std::string city, ident, country;
    double latitude, longitude;
    while (Airports_CSV->read_row(city, ident, latitude, longitude, country))
    {
        Airport newAirport(city + " " + InternationalAirport, ident, {latitude, longitude, country, city});
        s_Airports.push_back(newAirport);
    }
}
void AirportSimulation::GeneratePassengers()
{
    std::ifstream file(AirportsCSVFilepath);
    if (!file.is_open())
    {
        system("dir");
        DEBUG_ASSERT(0, "COULD NOT OPEN FILE.");
    }
    Passengers_CSV = new io::CSVReader<3>(PassengersCSVFilepath);
    Passengers_CSV->read_header(io::ignore_extra_column, "firstname", "surname", "date");
    std::string name;
    std::string surname;
    std::string date;
    while (Passengers_CSV->read_row(name, surname, date))
    {
        std::string y = date.substr(0, 4);
        std::string m = date.substr(5, 6);
        std::string d = date.substr(8, 9);
        int day = DURLIB::STOI(d);
        int month = DURLIB::STOI(m) - 1;
        int year = DURLIB::STOI(y);

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(40.0, 80.0);
        double randomWeight = std::floor(dist(mt));

        Passenger *newPassenger = new Passenger(name, surname, {year, (DURLIB::DateMath::Months)month, day}, randomWeight);

        std::random_device rd2;
        std::mt19937 mt2(rd2());
        std::uniform_real_distribution<double> dist2(0.0, 15.0);

        newPassenger->AddLuggageWeight(std::floor(dist2(mt2)) * CHAOS_FACTOR);

        s_Passengers.push_back(newPassenger);
    }
}
void AirportSimulation::GeneratePlanes()
{
    int AirportAmount = (int)s_Airports.size();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(AirportAmount, MaximumPlanes);
    int TotalPlaneAmount = dist(mt);

    for (int i = 0; i < TotalPlaneAmount; i++)
    {
        PlaneCounter++;
        std::random_device rd2;
        std::mt19937 mt2(rd2());
        std::uniform_int_distribution<size_t> dist2(0, s_Airports.size() - 1);
        size_t selectedAirport = dist2(mt2);

        std::random_device rd3;
        std::mt19937 mt3(rd3());
        std::uniform_int_distribution<int> dist3(0, 2);
        int selectedAirplaneType = dist3(mt3);

        s_Airports[selectedAirport].AddPlane((AirplaneType)selectedAirplaneType);
    }

    for (int i = 0; i < s_Airports.size(); i++)
    {
        if (s_Airports[i].GetLobbySize() == 0)
        {
            PlaneCounter++;
            s_Airports[i].AddPlane(AirplaneType::JUMBO_JET);
        }
    }
}
void AirportSimulation::AssignPassengersToAirports()
{
    int PeopleAmount = (int)s_Passengers.size();
    for (int i = 0; i < PeopleAmount + DEBUG_MAX_PEOPLE; i++)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<size_t> dist(0, s_Airports.size() - 1);
        size_t selectedAirport = dist(mt);

        s_Airports[selectedAirport].AddPerson(s_Passengers[i]);
    }
}

void AirportSimulation::PrintInformation()
{
    CLI_INFO("Generated Planes = {}", PlaneCounter);
    for (int i = 0; i < s_Airports.size(); i++)
    {
        CLI_TRACE("{} HAS {} PLANES", s_Airports[i].GetAirportName(), s_Airports[i].GetHangarSize());
    }
    CLI_INFO("Total generated people = {}", s_Passengers.size());
    for (int i = 0; i < s_Airports.size(); i++)
    {
        CLI_TRACE("{} HAS {} PEOPLE", s_Airports[i].GetAirportName(), s_Airports[i].GetLobbySize());
    }
}

void AirportSimulation::Execute()
{
    CalculateChaosFactor();

    GenerateAirports();
    GeneratePassengers();
    GeneratePlanes();
    AssignPassengersToAirports();

    // AIRPORTS
    Airport *AirportOne = nullptr;
    size_t a1 = -1;
    Airport *AirportTwo = nullptr;
    size_t a2 = -1;
    // GET AIRPORTS:
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<size_t> dist(0, s_Airports.size() - 1);
        a1 = dist(mt);
        AirportOne = &s_Airports[a1];
        a2 = a1;
    }
    while (a1 == a2)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<size_t> dist(0, s_Airports.size() - 1);
        a2 = dist(mt);
    }
    AirportTwo = &s_Airports[a2];
    // AIRPORTS

    // PLANES
    Airplane *PlaneFromAirportOne = nullptr;
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<size_t> dist(0, AirportOne->GetHangarSize() - 1);
        PlaneFromAirportOne = AirportOne->GetPlane(dist(mt));
    }
    Airplane *PlaneFromAirportTwo = nullptr;
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<size_t> dist(0, AirportTwo->GetHangarSize() - 1);
        PlaneFromAirportTwo = AirportTwo->GetPlane(dist(mt));
    }
    // PLANES

    // FILL PLANES WITH PASSENGERS
    for (int i = 0; i < AirportOne->GetLobbySize(); i++)
    {
        if (PlaneFromAirportOne->GetCurrentPassengers() >= PlaneFromAirportOne->GetMaxPassengers())
        {
            break;
        }
        Passenger *passenger = AirportOne->GetPassenger(i);
        PlaneFromAirportOne->AddPassenger(passenger);
    }
    for (int i = 0; i < AirportTwo->GetLobbySize(); i++)
    {
        if (PlaneFromAirportTwo->GetCurrentPassengers() >= PlaneFromAirportTwo->GetMaxPassengers())
        {
            break;
        }
        Passenger *passenger = AirportTwo->GetPassenger(i);
        PlaneFromAirportTwo->AddPassenger(passenger);
    }
    // FILL PLANES WITH PASSENGERS

    // RANDOMIZE FUEL TANKS
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0, PlaneFromAirportOne->GetMaxFuel());
        double FuelAmount = dist(mt);
        PlaneFromAirportOne->AddFuel(FuelAmount * CHAOS_PERCENTAGE);
    }
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0, PlaneFromAirportTwo->GetMaxFuel());
        double FuelAmount = dist(mt);
        PlaneFromAirportTwo->AddFuel(FuelAmount * CHAOS_PERCENTAGE);
    }
    // RANDOMIZE FUEL TANKS

    // LINK TWO AIRPORTS
    {
        PlaneFromAirportOne->SetAirportA(AirportOne);
        Airport *temp = nullptr;
        size_t b1 = a1;
        while (b1 == a1 || b1 == a2)
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<size_t> dist(0, s_Airports.size() - 1);
            b1 = dist(mt);
        }
        temp = &s_Airports[b1];
        PlaneFromAirportOne->SetAirportB(temp);
    }
    {
        PlaneFromAirportTwo->SetAirportA(AirportTwo);
        Airport *temp = nullptr;
        size_t b1 = a1;
        while (b1 == a1 || b1 == a2)
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<size_t> dist(0, s_Airports.size() - 1);
            b1 = dist(mt);
        }
        temp = &s_Airports[b1];
        PlaneFromAirportTwo->SetAirportB(temp);
    }
    // LINK TWO AIRPORTS

    // CALCULATE FLIGHT
    {
        double maxSpeed = PlaneFromAirportOne->GetMaxSpeed();
        double avgFuel = PlaneFromAirportOne->GetAverageFuelConsumption();
        PlaneFromAirportOne->CalculateFlight(maxSpeed, avgFuel);
    }
    {
        double maxSpeed = PlaneFromAirportTwo->GetMaxSpeed();
        double avgFuel = PlaneFromAirportTwo->GetAverageFuelConsumption();
        PlaneFromAirportTwo->CalculateFlight(maxSpeed, avgFuel);
    }
    // CALCULATE FLIGHT

    // PRINT INFORMATION
    // If verbose is set to true - print additional information.
    if (Verbose)
    {
        // AIRPORTS
        CLI_WARN("AIRPORTS:");

        CLI_TRACE("\t1. {}; People = {}, Planes = {};",
                  AirportOne->GetAirportName(), AirportOne->GetLobbySize(), AirportOne->GetHangarSize());

        CLI_TRACE("\t2. {}; People = {}, Planes = {}",
                  AirportTwo->GetAirportName(), AirportTwo->GetLobbySize(), AirportTwo->GetHangarSize());

        // PLANES AND PEOPLE
        CLI_WARN("PLANES AND PEOPLE:");

        CLI_TRACE("\t1. {} Plane (ID:{}, | INDEX: {}) has {} passengers.",
                  AirportOne->GetAirportName(), PlaneFromAirportOne->GetID(),
                  AirportOne->GetPlane(PlaneFromAirportOne->GetID())->GetID(),
                  PlaneFromAirportOne->GetCurrentPassengers());

        CLI_TRACE("\t2. {} Plane (ID:{}, | INDEX: {}) has {} passengers.",
                  AirportTwo->GetAirportName(), PlaneFromAirportTwo->GetID(),
                  AirportTwo->GetPlane(PlaneFromAirportTwo->GetID())->GetID(),
                  PlaneFromAirportTwo->GetCurrentPassengers());

        // DETAILED PLANE SPECIFICATION:
        CLI_WARN("PLANE SPECIFICS:");
        PlaneFromAirportOne->PrintAirplaneInformation();
        PlaneFromAirportTwo->PrintAirplaneInformation();

        // FLIGHT
        CLI_WARN("FLIGHT SPECIFICS:");
        PlaneFromAirportOne->PrintFlightInformation();
        PlaneFromAirportTwo->PrintFlightInformation();

        // DEBUG
        // CLI_WARN("Additional loop information:");
        // PrintInformation();
        // PRINT INFORMATION
    }

    // FLY
    CLI_WARN("STARTING FLIGHTS");
    PlaneFromAirportOne->Fly();
    PlaneFromAirportTwo->Fly();
    CLI_WARN("ENDING FLIGHTS");
    // FLY
}