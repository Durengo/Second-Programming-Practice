#include "AirportSimulation.h"

#include <durlib/Log/Log.h>
#include <durlib/Input/Input.h>

int main()
{
    DURLIB::Log::Init();

    size_t loops = 0;
    double chaos_percentage = -1;
    int chaos_rate = -1;
    char verbose = 'P';

    CLI_TRACE("Welcome to the small airport simulator\n\t\tThis small simulation will perform two plane flights from randomly selected airports.\n\t\tThe planes, passengers and their luggage (weight) will all be randomized and accounted for in the final fuel cost calculation for planes.\n\t\tThe end result of a singular loop will show the results of both planes.");
    CLI_INFO("RECOMMENDED VALUES: LOOPS < 100; CHAOS PERCENTAGE ~0.5; CHAOS RATE = 1000");

    while (loops == 0)
    {
        CLI_TRACE("Enter an amount of times to loop over the simulation. (MUST BE A NATURAL NUMBER):");
        loops = DURLIB::GIBI(1, INT_MAX);
    }
    while (chaos_percentage == -1)
    {
        CLI_TRACE("Enter the chaos percentage (unpredictability factor):");
        chaos_percentage = DURLIB::GIBD(0.0000000000000001, 0.9999999999999999);
    }
    while (chaos_rate == -1)
    {
        CLI_TRACE("Enter the chaos rate (natural numbers):");
        chaos_rate = DURLIB::GIBI(0, INT_MAX);
    }
    while (verbose == 'P')
    {
        CLI_TRACE("Enable verbose information?");
        verbose = DURLIB::YesOrNo();
    }

    CLI_INFO("ENTERED VALUES: LOOPS: {}, CHAOS PERCENTAGE: {}, CHAOS RATE: {}", loops, chaos_percentage, chaos_rate);

    for (size_t i = 0; i != loops; i++)
    {
        {
            AirportSimulation::Init();
            AirportSimulation::SetChaosPercentage(chaos_percentage);
            AirportSimulation::SetChaosRate(chaos_rate);
            AirportSimulation::SetVerbose(verbose);
            AirportSimulation::Execute();
            AirportSimulation::Destroy();
        }
    }

    CLI_INFO("ENTERED VALUES: LOOPS: {}, CHAOS PERCENTAGE: {}, CHAOS RATE: {}", loops, chaos_percentage, chaos_rate);

    CLI_WARN("PRESS ENTER TO EXIT.");
    std::cin.ignore();
    std::getchar();
    return 0;
}