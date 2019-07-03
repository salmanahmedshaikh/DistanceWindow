#include "incTrajLengthWindow.h"
#include "spatialDistance.h"


incTrajLengthWindow::incTrajLengthWindow()
{
    //ctor
}

incTrajLengthWindow::~incTrajLengthWindow()
{
    //dtor
}

void incTrajLengthWindow::insertElement(int trajectoryID, std::string timestamp, double longitude, double latitude)
{
    insertTuple(trajectoryID,timestamp,longitude,latitude);
    updateWindow(trajectoryID);
    //std::cout << "longitude " << longitude << ", latitude " << latitude << std::endl;
}

// Keep the size of the window within given limits
void incTrajLengthWindow::updateWindow(int trajectoryID)
{
    trajectoryMapIt = trajectoryMap.find(trajectoryID);

    if ( trajectoryMapIt == trajectoryMap.end() )
    {
        std::cout << "Trajectory with ID " << trajectoryID << " not found!" << std::endl;
    }
    else // if the trajectory already exists
    {
        std::list<std::tuple<std::string,double,double> >& trajectory = trajectoryMapIt->second;

        if (trajectory.size() == 1)
        {
            trajectoryLengthMapIt = trajectoryLengthMap.find(trajectoryID);

            // Insert only if not already exist
            if ( trajectoryLengthMapIt == trajectoryLengthMap.end() )
            {
                std::pair<int, double> trajectoryLengthPair (trajectoryID, 0.0);
                trajectoryLengthMap.insert(trajectoryLengthPair);
            }

            return;
        }
        else if(trajectory.size() > 1) // We cannot compute distance from a trajectory with size 1 or 0
        {
            double trajectoryLength = 0;

            trajectoryLengthMapIt = trajectoryLengthMap.find(trajectoryID);

            if ( trajectoryLengthMapIt != trajectoryLengthMap.end() )
            {
                trajectoryLength = trajectoryLengthMapIt->second;
            }
            else
            {
                std::cout << "Distance entry not found in trajectoryLengthMap";
                exit(0);
            }

            double twoPointsDistance = distBetweenTwoNewestPoints(trajectoryID);

            trajectoryLength += twoPointsDistance;
            //std::cout << trajectoryID << ", twoPointsDistance: " << twoPointsDistance << ", trajectoryLength: " << trajectoryLength << std::endl;

            // If the total trajectory length is greater than the window size then remove the oldest tuple from trajectory.
            while(trajectoryLength > mWindowSize)
            {                // we cannot remove the last element in the list, even it is greater than windowSize
                if(trajectory.size() > 1)
                {
                    double distance = distBetweenTwoOldestPoints(trajectoryID);
                    //std::cout << "DistBetweenOldestPoints " << distance << std::endl;

                    trajectoryLength -= distance;
                    deleteOldestTrajectoryTuple(trajectoryID);
                }
                else
                {
                    break;
                }
            }
            //std::cout << "Trajectory ID: " << trajectoryID << " | Length (m): " << trajectoryLength << ", #TrajElements: " << trajectory.size() << std::endl;

            //Updating trajectoryLengthMap
            trajectoryLengthMap[trajectoryID] = trajectoryLength;

            //mLongitude1 = longitude2;
            //mLatitude1 = latitude2;
        }
        else
        {
            std::cout << "Invalid trajectory size" << std::endl;
            exit(0);
        }

    }
}
