#include "spatialDistance.h"
#include <iostream>
#include <cmath>

uint64_t spatialDistance::mNumDistanceComputations = 0;

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

uint64_t spatialDistance::getNumDistanceComputations(void)
{
    return spatialDistance::mNumDistanceComputations;
}

double spatialDistance::roadDistance(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, float from_latitude, float from_longitude, float to_latitude, float to_longitude)
{
    unsigned from = map_geo_position.find_nearest_neighbor_within_radius(from_latitude, from_longitude, 500).id;
    //unsigned from = map_geo_position.find_nearest_neighbor_within_radius(40.87105, -73.86361, 1000).id;
    if(from == invalid_id){
        //std::cout << "No node within 1000m from source position" << std::endl;
        return 99999.99999;
    }

    unsigned to = map_geo_position.find_nearest_neighbor_within_radius(to_latitude, to_longitude, 1000).id;
    //unsigned to = map_geo_position.find_nearest_neighbor_within_radius(40.87332,-73.88967, 1000).id;
    if(to == invalid_id){
        //std::cout << "No node within 1000m from target position" << std::endl;
        return 99999.99999;
    }

    ch_query.reset();
    ch_query.add_source(from);
    ch_query.add_target(to);
    ch_query.run();
    //ch_query.reset().add_source(from).add_target(to).run();

    double distance = ch_query.get_distance();
    //std::cout << "road distance " << distance << std::endl;

    return distance;
}
