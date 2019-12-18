#include "incDistArrayWindow.h"
#include "spatialDistance.h"

incDistArrayWindow::incDistArrayWindow()
{
    //ctor
}

incDistArrayWindow::~incDistArrayWindow()
{
    //dtor
}

void incDistArrayWindow::insertElement(int trajectoryID, std::string timestamp, double longitude, double latitude)
{
    insertTuple(trajectoryID,timestamp,longitude,latitude);
    updateWindow(trajectoryID);
    deleteExpiredTrajectories();
}

// Keep the size of the window within given limits
void incDistArrayWindow::updateWindow(int trajectoryID)
{
    trajectoryMapIt = trajectoryMap.find(trajectoryID);
    std::list<double> trajectoryLengthsList;

    if ( trajectoryMapIt == trajectoryMap.end() )
    {
        std::cout << "Trajectory with ID " << trajectoryID << " not found!" << std::endl;
        return;
    }
    else // if the trajectory already exists
    {
        std::list<std::tuple<std::string,double,double> >& trajectory = trajectoryMapIt->second;

        if (trajectory.size() == 1)
        {
            trajectoryDistanceArrayMapIt = trajectoryDistanceArrayMap.find(trajectoryID);

            // Insert only if not already exist
            if ( trajectoryDistanceArrayMapIt == trajectoryDistanceArrayMap.end() )
            {
                // Pushing first tuple in trajectoryLengthsList
                trajectoryLengthsList.push_back(0.0);
                std::pair<int, std::list<double> > trajectoryLengthPair (trajectoryID, trajectoryLengthsList);
                trajectoryDistanceArrayMap.insert(trajectoryLengthPair);
            }


            return;
        }
        else if(trajectory.size() > 1) // We cannot compute distance from a trajectory with size 1 or 0
        {
            trajectoryDistanceArrayMapIt = trajectoryDistanceArrayMap.find(trajectoryID);

            if ( trajectoryDistanceArrayMapIt != trajectoryDistanceArrayMap.end() )
            {
                trajectoryLengthsList = trajectoryDistanceArrayMapIt->second;
            }
            else
            {
                std::cout << "Distance entry not found in trajectoryDistanceArrayMap";
                exit(0);
            }

            double trajectoryLength = 0;

            for (double trajLength : trajectoryLengthsList)
                trajectoryLength += trajLength;

            double twoPointsDistance = distBetweenTwoNewestPoints(trajectoryID);

            trajectoryLengthsList.push_back(twoPointsDistance);
            trajectoryLength += twoPointsDistance;
            //std::cout << trajectoryID << ", twoPointsDistance: " << twoPointsDistance << ", trajectoryLength: " << trajectoryLength << std::endl;

            // If the total trajectory length is greater than the window size then remove the oldest tuple from trajectory.
            while(trajectoryLength > mWindowSize)
            {                // we cannot remove the last element in the list, even it is greater than windowSize
                if(trajectory.size() > 1)
                {
                    double distance = trajectoryLengthsList.front();
                    trajectoryLengthsList.pop_front();
                    //std::cout << "DistBetweenOldestPoints " << distance << std::endl;

                    trajectoryLength -= distance;
                    deleteOldestTrajectoryTuple(trajectoryID);
                }
                else
                {
                    break;
                }
            }
            //std::cout << "Trajectory ID: " << trajectoryID << " | Length (m): " << trajectoryLength << ", #TrajElements: " << trajectory.size() << ", trajectoryLengthsList: " << trajectoryLengthsList.size() << std::endl;

            //Updating trajectoryDistanceArrayMap
            trajectoryDistanceArrayMap[trajectoryID] = trajectoryLengthsList;

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


double incDistArrayWindow::getTrajectoryLength(int trajectoryID)
{
    double trajectoryLength = 0;
    trajectoryMapIt = trajectoryMap.find(trajectoryID);
    std::list<double> trajectoryLengthsList;

    if ( trajectoryMapIt == trajectoryMap.end() )
    {
        std::cout << "Trajectory with ID " << trajectoryID << " not found!" << std::endl;
        exit(0);
    }
    else // if the trajectory already exists
    {
        std::list<std::tuple<std::string,double,double> >& trajectory = trajectoryMapIt->second;

        if (trajectory.size() == 1)
        {
            return trajectoryLength;
        }
        else if(trajectory.size() > 1) // We cannot compute distance from a trajectory with size 1 or 0
        {
            trajectoryDistanceArrayMapIt = trajectoryDistanceArrayMap.find(trajectoryID);

            if ( trajectoryDistanceArrayMapIt != trajectoryDistanceArrayMap.end() )
            {
                trajectoryLengthsList = trajectoryDistanceArrayMapIt->second;
            }
            else
            {
                std::cout << "Distance entry not found in trajectoryDistanceArrayMap";
                exit(0);
            }

            trajectoryLength = 0;

            for (double trajLength : trajectoryLengthsList)
                trajectoryLength += trajLength;

            return trajectoryLength;
        }
        else
        {
            std::cout << "Invalid trajectory size" << std::endl;
            exit(0);
        }
    }
}

