#include "EarthCoordinates.h"

#include <cmath>
#include <numbers>

namespace DURLIB
{
    double Harvesine(const EarthCoordinateSystem &first_coordinate, const EarthCoordinateSystem &second_coordinate)
    {
        double R = 6371000;
        double phi1 = first_coordinate.Latitude * std::numbers::pi / 180;
        double phi2 = second_coordinate.Latitude * std::numbers::pi / 180;
        double delta_phi = (second_coordinate.Latitude - first_coordinate.Latitude) * std::numbers::pi / 180;
        double delta_lambda = (second_coordinate.Longitude - first_coordinate.Longitude) * std::numbers::pi / 180;

        double a = std::sin(delta_phi / 2) * std::sin(delta_phi / 2) +
                   std::cos(delta_phi * 1) * std::cos(delta_phi * 2) *
                       std::sin(delta_lambda / 2) * std::sin(delta_lambda / 2);

        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
        // in meters
        return R * c;
    }

    double Spherical_Law_Of_Cosines(const EarthCoordinateSystem &first_coordinate, const EarthCoordinateSystem &second_coordinate)
    {
        double R = 6371000;
        double phi1 = first_coordinate.Latitude * std::numbers::pi / 180;
        double phi2 = second_coordinate.Latitude * std::numbers::pi / 180;
        double lambda = (second_coordinate.Longitude - first_coordinate.Longitude) * std::numbers::pi / 180;
        return std::acos(std::sin(phi1) * std::sin(phi2) + std::cos(phi1) * std::cos(phi2) * std::cos(lambda)) * R;
    }
}