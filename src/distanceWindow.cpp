#include "distanceWindow.h"
#include "spatialDistance.h"

distanceWindow::distanceWindow()
{
    //ctor
}

/*
distanceWindow::distanceWindow(int windowSize)
{
    mWindowSize = windowSize;
}
*/

distanceWindow::~distanceWindow()
{
    //dtor
}

void distanceWindow::setWindowSize(int windowSize)
{
    mWindowSize = windowSize;
}

int distanceWindow::getWindowSize(void)
{
    return mWindowSize;
}



void distanceWindow::insertTuple(int trajectoryID, std::string timestamp, double longitude, double latitude)
{
    trajectoryMapIt = trajectoryMap.find(trajectoryID);

    if ( trajectoryMapIt == trajectoryMap.end() )
    {
        //std::cout << "Trajectory with ID " << trajectoryID << " does not exist. Creating!" << std::endl;
        // Creating a list trajectory
        std::list<std::tuple<std::string,double,double> > trajectory;
        // Pushing first tuple in it
        trajectory.push_back( make_tuple (timestamp, longitude, latitude) );
        // Creating trajectoryTuple pair
        std::pair<int, std::list<std::tuple<std::string,double,double>> > trajectoryTuple (trajectoryID, trajectory);
        //trajectoryMap.insert(make_pair<int, list<tuple<string,double,double> >>(trajectoryID, trajectory));
        //Inserting trajectory into trajectory map
        trajectoryMap.insert(trajectoryTuple);
    }
    else
    {
        // Inserting new tuple in trajectory list
        std::list<std::tuple<std::string,double,double> >& trajectory = trajectoryMapIt->second;
        trajectory.push_back( make_tuple (timestamp, longitude, latitude) );

        //Updating trajectoryMap
        trajectoryMap[trajectoryID] = trajectory;
    }

    return;
}


void distanceWindow::listAllTrajectories()
{
    for(trajectoryMapIt = trajectoryMap.begin(); trajectoryMapIt != trajectoryMap.end(); trajectoryMapIt++)
    {
        if ( trajectoryMapIt != trajectoryMap.end() )
        {
            int trajectoryID = trajectoryMapIt->first;
            std::list<std::tuple<std::string,double,double> > trajectory = trajectoryMapIt->second;

            for (auto& trajTuple : trajectory)
            {
                std::cout << trajectoryID << ", " << std::get<0>(trajTuple) << ", " << std::get<1>(trajTuple) << ", " << std::get<2>(trajTuple) << std::endl;
            }
        }
    }

    return;
}


int distanceWindow::getNumOfTrajectories()
{
    return trajectoryMap.size();
}

void distanceWindow::deleteOldestTrajectoryTuple(int trajectoryID)
{
    trajectoryMapIt = trajectoryMap.find(trajectoryID);

    if ( trajectoryMapIt == trajectoryMap.end() )
    {
        std::cout << "Trajectory with ID " << trajectoryID << " not found!" << std::endl;
    }
    else
    {
        std::list<std::tuple<std::string,double,double> >& trajectory = trajectoryMapIt->second;

        if(!trajectory.empty())
            trajectory.pop_front();
    }

    return;
}


double distanceWindow::distBetweenTwoOldestPoints(int trajectoryID)
{
    double distance = 0;
    trajectoryMapIt = trajectoryMap.find(trajectoryID);

    if ( trajectoryMapIt == trajectoryMap.end() )
    {
        std::cout << "Trajectory with ID " << trajectoryID << " not found!" << std::endl;
    }
    else
    {
        std::list<std::tuple<std::string,double,double> >& trajectory = trajectoryMapIt->second;

        // Distance computation require at least 2 points
        if(trajectory.size() > 1)
        {
            std::list<std::tuple<std::string,double,double> >::iterator trajectoryIt;

            // Front of list always contain the oldest element as the insertion is done via push_back at the end of the queue
            trajectoryIt = trajectory.begin();

            auto& trajTuple1 = *trajectoryIt;
            double longitude1 = std::get<1>(trajTuple1);
            double latitude1 = std::get<2>(trajTuple1);
            //std::cout << "trajTuple1 " << trajectoryID << ", " << std::get<0>(trajTuple1) << ", " << std::get<1>(trajTuple1) << ", " << std::get<2>(trajTuple1) << std::endl;

            ++trajectoryIt;

            auto& trajTuple2 = *trajectoryIt;
            double longitude2 = std::get<1>(trajTuple2);
            double latitude2 = std::get<2>(trajTuple2);
            //std::cout << "trajTuple2 " << trajectoryID << ", " << std::get<0>(trajTuple2) << ", " << std::get<1>(trajTuple2) << ", " << std::get<2>(trajTuple2) << std::endl;

            spatialDistance sd;

            #ifdef HAVERSINE
                distance = sd.haversine(latitude1,longitude1,latitude2,longitude2);
            #elif defined EQUIRECTANGULAR
                distance = sd.equirectangular(latitude1,longitude1,latitude2,longitude2);
            #elif defined SPHERICALLAWOFCOSINES
                distance = sd.sphericalLawOfCosines(latitude1,longitude1,latitude2,longitude2);
            #endif

            /*
            for (trajectoryIt = trajectory.begin(); trajectoryIt != trajectory.end(); ++trajectoryIt)
            {
                auto& trajTuple = *trajectoryIt;
                std::cout << "Forward: " << trajectoryID << ", " << std::get<0>(trajTuple) << ", " << std::get<1>(trajTuple) << ", " << std::get<2>(trajTuple) << std::endl;
            }
            */
        }
    }

    return distance;
}

double distanceWindow::distBetweenTwoNewestPoints(int trajectoryID)
{
    double distance = 0;
    trajectoryMapIt = trajectoryMap.find(trajectoryID);

    if ( trajectoryMapIt == trajectoryMap.end() )
    {
        std::cout << "Trajectory with ID " << trajectoryID << " not found!" << std::endl;
    }
    else
    {
        std::list<std::tuple<std::string,double,double> >& trajectory = trajectoryMapIt->second;

        // Distance computation require at least 2 points
        if(trajectory.size() > 1)
        {

            std::list<std::tuple<std::string,double,double> >::reverse_iterator trajectoryRIt;

            // Back of list always contains the newest element as the insertion is done via push_back at the end of the queue
            trajectoryRIt = trajectory.rbegin();

            auto& trajTuple1 = *trajectoryRIt;
            double longitude1 = std::get<1>(trajTuple1);
            double latitude1 = std::get<2>(trajTuple1);
            //std::cout << "trajTuple1 " << trajectoryID << ", " << std::get<0>(trajTuple1) << ", " << std::get<1>(trajTuple1) << ", " << std::get<2>(trajTuple1) << std::endl;

            ++trajectoryRIt;

            auto& trajTuple2 = *trajectoryRIt;
            double longitude2 = std::get<1>(trajTuple2);
            double latitude2 = std::get<2>(trajTuple2);

            spatialDistance sd;

            #ifdef HAVERSINE
                distance = sd.haversine(latitude1,longitude1,latitude2,longitude2);
            #elif defined EQUIRECTANGULAR
                distance = sd.equirectangular(latitude1,longitude1,latitude2,longitude2);
            #elif defined SPHERICALLAWOFCOSINES
                distance = sd.sphericalLawOfCosines(latitude1,longitude1,latitude2,longitude2);
            #endif
        }
    }

    return distance;
}




