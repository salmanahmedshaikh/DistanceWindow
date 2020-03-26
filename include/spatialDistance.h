#pragma once
#include "stdafx.h"
#include <stdint.h>
#include <routingkit/geo_position_to_node.h>
#include <routingkit/contraction_hierarchy.h>

using namespace RoutingKit;


class spatialDistance
{
    public:
        spatialDistance();
        virtual ~spatialDistance();

        double haversine(double lat1, double lon1, double lat2, double lon2);
        double equirectangular(double lat1, double lon1, double lat2, double lon2);
        double sphericalLawOfCosines(double lat1, double lon1, double lat2, double lon2);
        uint64_t getNumDistanceComputations(void);
        double roadDistance(GeoPositionToNode map_geo_position, ContractionHierarchyQuery ch_query, float from_latitude, float from_longitude, float to_latitude, float to_longitude);



    protected:

    private:
        const double mEARTH_RADIUS = 6371008.7714; // Earth radius in meters
        static uint64_t mNumDistanceComputations;

        double degreesToRadians(double degValue);

};
