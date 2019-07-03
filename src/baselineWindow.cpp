#include "baselineWindow.h"
#include "spatialDistance.h"

baselineWindow::baselineWindow()
{
    //ctor
}

baselineWindow::~baselineWindow()
{
    //dtor
}

void baselineWindow::insertElement(int trajectoryID, std::string timestamp, double longitude, double latitude)
{
    insertTuple(trajectoryID,timestamp,longitude,latitude);
    updateWindow(trajectoryID);
}

// Keep the size of the window within given limits
void baselineWindow::updateWindow(int trajectoryID)
{
    trajectoryMapIt = trajectoryMap.find(trajectoryID);

    if ( trajectoryMapIt == trajectoryMap.end() )
    {
        std::cout << "Trajectory with ID " << trajectoryID << " not found!" << std::endl;
    }
    else
    {
        std::list<std::tuple<std::string,double,double> >& trajectory = trajectoryMapIt->second;

         // We cannot compute distance from a trajectory with size 1 or 0
        if(trajectory.size() > 1)
        {
            double trajectoryLength = -999;
            double longitude1 = 0;
            double latitude1 = 0;
            double longitude2 = 0;
            double latitude2 = 0;
            std::list<double> distanceList;

            spatialDistance sd;

            for (auto& trajTuple : trajectory)
            {
                if(trajectoryLength == -999) // executed only once
                {
                    longitude1 = std::get<1>(trajTuple);
                    latitude1 = std::get<2>(trajTuple);
                    trajectoryLength = 0;
                }
                else
                {
                    longitude2 = std::get<1>(trajTuple);
                    latitude2 = std::get<2>(trajTuple);

                    double distance = 0;

                    #ifdef HAVERSINE
                        distance = sd.haversine(latitude1,longitude1,latitude2,longitude2);
                        //std::cout << "HAVERSINE" << std::endl;
                    #elif defined EQUIRECTANGULAR
                        distance = sd.equirectangular(latitude1,longitude1,latitude2,longitude2);
                    #elif defined SPHERICALLAWOFCOSINES
                        distance = sd.sphericalLawOfCosines(latitude1,longitude1,latitude2,longitude2);
                    #endif

                    distanceList.push_back(distance);
                    trajectoryLength += distance;

                    //std::cout << "Trajectory ID: " << trajectoryID << " | Haversine distance: " << distance << std::endl;

                    longitude1 = longitude2;
                    latitude1 = latitude2;
                }
            }

            // If the total trajectory length is greater than the window size then remove the oldest tuple from trajectory.
            while(trajectoryLength > mWindowSize)
            {
                // we cannot remove the last element in the list, even it is greater than windowSize
                if(distanceList.size() > 1)
                {
                    deleteOldestTrajectoryTuple(trajectoryID);
                    trajectoryLength -= distanceList.front();
                    distanceList.pop_front();
                }
                else
                {
                    break;
                }
            }
            //std::cout << "Trajectory ID: " << trajectoryID << " | Length (m): " << trajectoryLength << ", #TrajElements: " << trajectory.size() << std::endl;
        }
    }
}





