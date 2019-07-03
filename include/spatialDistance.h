#include "stdafx.h"


class spatialDistance
{
    public:
        spatialDistance();
        virtual ~spatialDistance();

        double haversine(double lat1, double lon1, double lat2, double lon2);
        double equirectangular(double lat1, double lon1, double lat2, double lon2);
        double sphericalLawOfCosines(double lat1, double lon1, double lat2, double lon2);
        int getNumDistanceComputations(void);



    protected:

    private:
        const double mEARTH_RADIUS = 6371008.7714; // Earth radius in meters
        static int mNumDistanceComputations;

        double degreesToRadians(double degValue);

};
