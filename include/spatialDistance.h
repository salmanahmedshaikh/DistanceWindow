#pragma once
#include "stdafx.h"
#include <stdint.h>



class spatialDistance
{
    public:
        spatialDistance();
        virtual ~spatialDistance();

        double haversine(double lat1, double lon1, double lat2, double lon2);
        double equirectangular(double lat1, double lon1, double lat2, double lon2);
        double sphericalLawOfCosines(double lat1, double lon1, double lat2, double lon2);
        uint64_t getNumDistanceComputations(void);



    protected:

    private:
        const double mEARTH_RADIUS = 6371008.7714; // Earth radius in meters
        static uint64_t mNumDistanceComputations;

        double degreesToRadians(double degValue);

};
