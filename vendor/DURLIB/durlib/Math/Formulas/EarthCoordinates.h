#pragma once

namespace DURLIB
{
    struct EarthCoordinateSystem
    {
        double Latitude;
        double Longitude;
    };

    double Harvesine(const EarthCoordinateSystem &first_coordinate, const EarthCoordinateSystem &second_coordinate);
    double Spherical_Law_Of_Cosines(const EarthCoordinateSystem &first_coordinate, const EarthCoordinateSystem &second_coordinate);
}