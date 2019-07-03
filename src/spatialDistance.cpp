#include "spatialDistance.h"
#include <iostream>
#include <cmath>

int spatialDistance::mNumDistanceComputations = 0;

spatialDistance::spatialDistance()
{
    //ctor
}

spatialDistance::~spatialDistance()
{
    //dtor
}

double spatialDistance::haversine(double lat1, double lon1, double lat2, double lon2)
{
    // If both the points are same, return 0
    if(lat1 == lat2 && lon1 == lon2)
        return 0;

    // distance between latitudes and longitudes
    double dLat = degreesToRadians(lat2 - lat1);
    double dLon = degreesToRadians(lon2 - lon1);

    // convert to radians
    lat1 = degreesToRadians(lat1);
    lat2 = degreesToRadians(lat2);

    // apply formulae
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));
    spatialDistance::mNumDistanceComputations++;

    return mEARTH_RADIUS * c;
}

double spatialDistance::equirectangular(double lat1, double lon1, double lat2, double lon2)
{
    // If both the points are same, return 0
    if(lat1 == lat2 && lon1 == lon2)
        return 0;

    double x = degreesToRadians(abs(lon2) - abs(lon1)) * cos(degreesToRadians(lat1 + lat2)/2);
    double y = degreesToRadians(lat2 - lat1);
    spatialDistance::mNumDistanceComputations++;

    return mEARTH_RADIUS * sqrt(pow(x,2) + pow(y,2));
}

double spatialDistance::sphericalLawOfCosines(double lat1, double lon1, double lat2, double lon2)
{
    // If both the points are same, return 0
    if(lat1 == lat2 && lon1 == lon2)
        return 0;

    double rLat1 = degreesToRadians(lat1);
    double rLat2 = degreesToRadians(lat2);
    double dLon = degreesToRadians(lon2 - lon1);
    spatialDistance::mNumDistanceComputations++;

    return acos( sin(rLat1) * sin(rLat2) + cos(rLat1) * cos(rLat2) * cos(dLon) ) * mEARTH_RADIUS;
}

double spatialDistance::degreesToRadians(double degValue)
{
    return degValue * M_PI / 180.0;
}

int spatialDistance::getNumDistanceComputations(void)
{
    return spatialDistance::mNumDistanceComputations;
}
